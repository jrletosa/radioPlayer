#ifndef RADIOMANAGER_H
#define RADIOMANAGER_H

#include "RadioStationsContainer.h"

class RadioListViewHandler;

class RadioListHandler
{
public:

    virtual void setRadio(radioID &radio, const std::string &streamSource) = 0;
};

class RadioManager: public RadioListHandler
{
public:
    RadioManager();

    void setRadioListViewHandler(const RadioListViewHandler *listHandler);

    void addRadio(radioID &radio, const std::string &streamSource);
    void removeRadio(radioID &radio);
    void playRadio(radioID &radio);

    // add pause, stop...

protected:

    void setRadio(radioID &radio, const std::string &streamSource);

private:

    RadioStationsContainer m_radioContainer;
    RadioListViewHandler *m_listViewHandler;
};

#endif // RADIOMANAGER_H
