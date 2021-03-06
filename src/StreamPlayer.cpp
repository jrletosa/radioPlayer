#include "StreamPlayer.h"
#include <stdlib.h>
#include <iostream>
#include "fmod.hpp"
#include "fmod/common.h"
#include "fmod_errors.h"

void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}


StreamPlayer::StreamPlayer()
    : m_currentState(STOP)
    , m_playingThread(NULL)
{
}


StreamPlayer::~StreamPlayer()
{
    if (m_playingThread != NULL)
    {
        delete m_playingThread;
    }
}


void StreamPlayer::play(const std::string &streamSource)
{
    switch (m_currentState)
    {
        case STOP:
        {
            changeState(PLAY);
            m_playingThread= new std::thread(&StreamPlayer::playStream_Internal, this, streamSource);
        }break;
    }
}


void StreamPlayer::stop()
{
    switch (m_currentState)
    {
        case PLAY:
        {
            changeState(STOP);

            if (m_playingThread != NULL)
            {
                m_playingThread->join();
                delete m_playingThread;
                m_playingThread= NULL;
            }
        }break;
    }
}

void StreamPlayer::pause()
{
    switch (m_currentState)
    {
        case PLAY:
        {
            changeState(PAUSE);
        }break;

        case PAUSE:
        {
            changeState(PLAY);
        }break;
    }
}


void StreamPlayer::changeState(RadioPlayerState state)
{
    std::lock_guard<std::mutex> lock(m_currentStateMutex);

    m_currentState= state;
}


StreamPlayer::RadioPlayerState StreamPlayer::getState() const
{
    std::lock_guard<std::mutex> lock(m_currentStateMutex);

    return m_currentState;
}


void StreamPlayer::playStream_Internal(const std::string streamSource)
{
    FMOD::System    *system = 0;
    FMOD::Sound     *sound = 0;
    FMOD::Channel   *channel = 0;
    FMOD_RESULT      result = FMOD_OK;
    FMOD_OPENSTATE   openstate = FMOD_OPENSTATE_READY;
    unsigned int     version = 0;
    void            *extradriverdata = 0;
    const int        tagcount = 4;
    int              tagindex = 0;
    char             tagstring[tagcount][128] = { 0 };

    // jrletosa crashes
    //Common_Init(&extraDriverData);

    result= FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }

    //result = system->init(1, FMOD_INIT_NORMAL, extraDriverData);
    result = system->init(1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /* Increase the file buffer size a little bit to account for Internet lag. */
    result = system->setStreamBufferSize(64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);

    //result = system->createSound("http://shoutmedia.abc.net.au:10426", FMOD_CREATESTREAM | FMOD_NONBLOCKING, 0, &sound);
    //result = system->createSound("http://195.55.74.224/cope/rockfm.mp3?GKID=7c175e00f02d11e4a49e00163e914f69&fspref=aHR0cDovL3BsYXllci5yb2NrZm0uZm0vc3dmL3ZpZGVvL3BsYXllci5zd2Y%3D", FMOD_CREATESTREAM | FMOD_NONBLOCKING, 0, &sound);
    result = system->createSound(streamSource.c_str(), FMOD_CREATESTREAM | FMOD_NONBLOCKING, 0, &sound);
    ERRCHECK(result);

    /*
            Main loop
    */
    do
    {
        unsigned int    pos = 0;
        unsigned int    percent = 0;
        bool            playing = false;
        bool            paused = false;
        bool            starving = false;
        const char     *state = "Stopped";

        Common_Update();

        if (channel != NULL)
        {
            bool pause= (getState() == RadioPlayerState::PAUSE);
            bool currentPause= pause;
            result = channel->getPaused(&currentPause);
            ERRCHECK(result);
            if (pause != currentPause)
            {
                result = channel->setPaused(pause);
                ERRCHECK(result);
            }
        }

        result = system->update();
        ERRCHECK(result);

        result = sound->getOpenState(&openstate, &percent, &starving, 0);
        ERRCHECK(result);

        if (channel)
        {
            FMOD_TAG tag;

            /*
                Read any tags that have arrived, this could happen if a radio station switches
                to a new song.
            */
            while (sound->getTag(0, -1, &tag) == FMOD_OK)
            {
                if (tag.datatype == FMOD_TAGDATATYPE_STRING)
                {
                    sprintf(tagstring[tagindex], "%s = '%s' (%d bytes)", tag.name, (char *)tag.data, tag.datalen);
                    tagindex = (tagindex + 1) % tagcount;
                }
                else if (tag.type == FMOD_TAGTYPE_FMOD)
                {
                    /* When a song changes, the sample rate may also change, so compensate here. */
                    if (!strcmp(tag.name, "Sample Rate Change"))
                    {
                        float frequency = *((float *)tag.data);

                        result = channel->setFrequency(frequency);
                        ERRCHECK(result);
                    }
                }
            }

            result = channel->getPaused(&paused);
            ERRCHECK(result);

            result = channel->isPlaying(&playing);
            ERRCHECK(result);

            result = channel->getPosition(&pos, FMOD_TIMEUNIT_MS);
            ERRCHECK(result);

            /* Silence the stream until we have sufficient data for smooth playback. */
            result = channel->setMute(starving);
            ERRCHECK(result);
        }
        else
        {
             /* This may fail if the stream isn't ready yet, so don't check the error code. */
            system->playSound(sound, 0, false, &channel);
        }

        if (openstate == FMOD_OPENSTATE_BUFFERING)
        {
            state = "Buffering...";
        }
        else if (openstate == FMOD_OPENSTATE_CONNECTING)
        {
            state = "Connecting...";
        }
        else if (paused)
        {
            state = "Paused";
        }
        else if (playing)
        {
            state = "Playing";
        }

        Common_Draw("==================================================");
        Common_Draw("Net Stream Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2004-2015.");
        Common_Draw("==================================================");
        Common_Draw("");
        Common_Draw("Press %s to toggle pause", Common_BtnStr(BTN_ACTION1));
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");
        Common_Draw("Time = %02d:%02d:%02d", pos / 1000 / 60, pos / 1000 % 60, pos / 10 % 100);
        Common_Draw("State = %s %s", state, starving ? "(STARVING)" : "");
        Common_Draw("Buffer Percentage = %d", percent);
        Common_Draw("");
        Common_Draw("Tags:");
        for (int i = tagindex; i < (tagindex + tagcount); i++)
        {
            Common_Draw("%s", tagstring[i % tagcount]);
            Common_Draw("");
        }

        Common_Sleep(50);
    } while(!(getState() == RadioPlayerState::STOP));

    /*
        Stop the channel, then wait for it to finish opening before we release it.
    */
    if (channel)
    {
        result = channel->stop();
        ERRCHECK(result);
    }

    do
    {
        Common_Update();
        Common_Draw("Waiting for sound to finish opening before trying to release it....", Common_BtnStr(BTN_ACTION1));
        Common_Sleep(50);

        result = system->update();
        ERRCHECK(result);

        result = sound->getOpenState(&openstate, 0, 0, 0);
        ERRCHECK(result);
    } while (openstate != FMOD_OPENSTATE_READY);

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();
}
