#include "RadioManager.h"
#include "StreamPlayer.h"


RadioManager::RadioManager()
{
}


void RadioManager::addRadio(radioID &radio, const std::string &streamSource)
{
    m_radioContainer.addRadioStation(radio, streamSource);
}


void RadioManager::removeRadio(radioID &radio)
{
    // jrletosa stop playing if removed station is currently playing?
    m_radioContainer.removeRadioStation(radio);
}


void RadioManager::playRadio(radioID &radio)
{
    std::string stream;
    m_radioContainer.getStreamURL(radio, stream);
    if (!stream.empty())
    {
        StreamPlayer player;
        player.playStream(stream);
    }
}
