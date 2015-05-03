#ifndef RADIOSTATIONSCONTAINER_H
#define RADIOSTATIONSCONTAINER_H

#include <string>
#include <map>

typedef const std::string radioID;

class RadioStationsContainer
{
public:
    typedef std::map<radioID, std::string> StationsMap;

    RadioStationsContainer();

    void addRadioStation(radioID &radioName, const std::string &streamSource);
    void removeRadioStation(radioID &radioName);
    void getStreamURL(radioID &radioName, std::string &streamURL) const;

    StationsMap getRadioMap() const;

private:

    StationsMap m_radioMap;
};

#endif // RADIOSTATIONSCONTAINER_H
