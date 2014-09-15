
#ifndef MESSAGTYPES_H
#define MESSAGTYPES_H

#include <array>
#include "globals.h"
#include "oscpkt.hh"
#include "oscaddressreader.h"

struct BufferMessage
{

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

struct OscDeviceMessage
{
    const oscpkt::Message &msg;
    OscAddressReader &addReader;

    OscDeviceMessage(const oscpkt::Message &_msg, OscAddressReader &_addReader) :
        msg(_msg),
        addReader(_addReader)
    {
        LOG(__PRETTY_FUNCTION__);
    }
};

enum DEVICE_STATE{
    CONNECTED = 0,
    DISCONNECTED = 1,
    CONNECTING = -1,
    ERROR = -2
};

struct DeviceStateMessage
{
    const DEVICE_STATE &state;
    const std::string &status;
    const std::string &name;

    DeviceStateMessage(const DEVICE_STATE &_state, const std::string &_status, const std::string &_name) :
        state(_state),
        status(_status),
        name(_name)
    {
        LOG(__PRETTY_FUNCTION__);
    }
};

struct DeviceAddedMessage
{
    const std::string &name;
    const DEVICE_STATE &state;

    DeviceAddedMessage(const std::string &_name, const DEVICE_STATE &_state) :
        name(_name),
        state(_state)
    {
        LOG(__PRETTY_FUNCTION__);
    }
};

struct DeviceRemovedMessage{
    const std::string &name;

    DeviceRemovedMessage(const std::string &_name) :
        name(_name)
    {
        LOG(__PRETTY_FUNCTION__);
    }
};

#endif // MESSAGTYPES_H
