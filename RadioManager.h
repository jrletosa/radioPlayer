#ifndef RADIOMANAGER_H
#define RADIOMANAGER_H

#include "RadioStationsContainer.h"

class RadioManager
{
public:
    RadioManager();

    void addRadio(radioID &radio, const std::string &streamSource);
    void removeRadio(radioID &radio);
    void playRadio(radioID &radio);

    // add pause, stop...

private:

    RadioStationsContainer m_radioContainer;
};

#endif // RADIOMANAGER_H
