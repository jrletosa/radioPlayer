#include "RadioManager.h"
#include "StreamPlayer.h"
#include "MainWindow.h"

RadioManager::RadioManager()
    : m_listViewHandler(NULL)
    , m_currentPlayer(NULL)
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


void RadioManager::createStreamPlayer()
{
    if (m_currentPlayer != NULL)
    {
        delete m_currentPlayer;
        m_currentPlayer= NULL;
    }

    m_currentPlayer= new StreamPlayer();
}


void RadioManager::playRadio(radioID &radio)
{
    std::string stream;
    m_radioContainer.getStreamURL(radio, stream);
    if (!stream.empty())
    {
        createStreamPlayer();
        m_currentPlayer->play(stream);
    }
}


void RadioManager::pause()
{
    m_currentPlayer->pause();
}


void RadioManager::stop()
{
    m_currentPlayer->stop();
}


void RadioManager::setRadio(radioID &radio, const std::string &streamSource)
{
    addRadio(radio, streamSource);
}
