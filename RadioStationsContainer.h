#ifndef RADIOSTATIONSCONTAINER_H
#define RADIOSTATIONSCONTAINER_H

#include <string>
#include <map>

typedef const std::string radioID;

class RadioStationsContainer
{
public:
    RadioStationsContainer();

    void addRadioStation(radioID &radioName, const std::string &streamSource);
    void removeRadioStation(radioID &radioName);
    void getStreamURL(radioID &radioName, std::string &streamURL);

private:

    typedef std::map<radioID, std::string> StationsMap;
    StationsMap m_radioMap;
};

#endif // RADIOSTATIONSCONTAINER_H
