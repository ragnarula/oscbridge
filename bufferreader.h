#ifndef BUFFERREADER_H
#define BUFFERREADER_H

#include <array>
#include <iostream>
#include <thread>
#include <utility>
#include "globals.h"
#include "messaging.hpp"
#include "messagtypes.h"
#include "oscpkt.hh"

class BufferReader : public messaging::IMessageListener<BufferMessage>
{
    void processBuffer(std::unique_ptr<oscpkt::PacketReader>);
    virtual void handleMessage(const BufferMessage&);
public:
    BufferReader();
    virtual ~BufferReader();

};

#endif // BUFFERREADER_H
