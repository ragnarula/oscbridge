#ifndef MESSAGTYPES_H
#define MESSAGTYPES_H

#include <array>
#include "globals.h"

struct BufferMessage {

    const std::array<char, MAX_RECEIVE_BUFFER> &buffer;
    const std::size_t &howMany;

    BufferMessage(const std::array<char, MAX_RECEIVE_BUFFER> &_buffer,
                  const std::size_t &_howMany) :
        buffer(_buffer), howMany(_howMany)
    {
        LOG(__PRETTY_FUNCTION__);
    }

    ~BufferMessage()
    {
        LOG(__PRETTY_FUNCTION__);
    }
};

#endif // MESSAGTYPES_H
