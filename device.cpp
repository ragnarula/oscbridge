#include "device.h"

Device::Device() :
    currentState(DEVICE_STATE::DISCONNECTED)
{
}

void Device::setState(const DEVICE_STATE &_state, const std::string &_status)
{
    if(currentState == _state && status.compare(_status)){
        LOG(__PRETTY_FUNCTION__, " no change ", _state);
        return;
    }
    LOG(__PRETTY_FUNCTION__, " ", _state);
    currentState = _state;
    status = _status;
    DeviceStateMessage msg(currentState, status, name);
    messaging::send<DeviceStateMessage>(this,msg);
}

DEVICE_STATE Device::getState()
{
    LOG(__PRETTY_FUNCTION__);
    return currentState;
}

void Device::setName(const std::string &_name)
{
    LOG(__PRETTY_FUNCTION__);
    name = _name;
}

std::string& Device::getName()
{
    LOG(__PRETTY_FUNCTION__);
    return name;
}
