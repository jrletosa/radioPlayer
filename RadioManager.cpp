#include "RadioManager.h"
#include "StreamPlayer.h"
#include "MainWindow.h"

RadioManager::RadioManager()
{
}


void RadioManager::setRadioListViewHandler(const RadioListViewHandler *listHandler)
{
    m_listViewHandler= const_cast<RadioListViewHandler *>(listHandler);
}


void RadioManager::addRadio(radioID &radio, const std::string &streamSource)
{
    m_radioContainer.addRadioStation(radio, streamSource);
    if (m_listViewHandler != NULL)
    {
        m_listViewHandler->updateList(m_radioContainer);
    }
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


void RadioManager::setRadio(radioID &radio, const std::string &streamSource)
{
    addRadio(radio, streamSource);
}
