#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <string>
#include <mutex>
#include <thread>

class StreamPlayer
{
public:

    enum RadioPlayerState
    {
        STOP,
        PLAY,
        PAUSE
    };

    StreamPlayer();
    ~StreamPlayer();

    void play(const std::string &streamSource);
    void stop();
    void pause();

private:

    void changeState(RadioPlayerState state);
    void playStream_Internal(const std::string streamSource);

    RadioPlayerState getState() const;

    mutable std::mutex m_currentStateMutex;
    RadioPlayerState m_currentState;
    std::thread *m_playingThread;

};

#endif // STREAMPLAYER_H
