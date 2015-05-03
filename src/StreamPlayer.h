#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <string>

class StreamPlayer
{
public:
    StreamPlayer();

    void playStream(const std::string &streamSource);

private:

    void playStream_Internal(const std::string streamSource);
};

#endif // STREAMPLAYER_H
