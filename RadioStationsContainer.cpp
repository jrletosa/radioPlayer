#include "RadioStationsContainer.h"

RadioStationsContainer::RadioStationsContainer()
{
}


void RadioStationsContainer::addRadioStation(radioID &radioName, const std::string &streamSource)
{
    m_radioMap.insert(StationsMap::value_type(radioName, streamSource));
}


void RadioStationsContainer::removeRadioStation(radioID &radioName)
{
    m_radioMap.erase(radioName);
}


void RadioStationsContainer::getStreamURL(radioID &radioName, std::string &streamURL)
{
    streamURL.clear();
    StationsMap::const_iterator itMap= m_radioMap.find(radioName);
    if (itMap != m_radioMap.end())
    {
        streamURL= itMap->second;
    }
}
