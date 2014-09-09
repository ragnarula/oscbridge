#include "bufferreader.h"

BufferReader::BufferReader()
{
    LOG(__PRETTY_FUNCTION__);
}

BufferReader::~BufferReader()
{
    LOG(__PRETTY_FUNCTION__);
}

void BufferReader::processBuffer(std::unique_ptr<oscpkt::PacketReader> _ptrPacketReader)
{
    LOG(__PRETTY_FUNCTION__);
    oscpkt::Message *msg;
    while (_ptrPacketReader->isOk() && (msg = _ptrPacketReader->popMessage()) != 0) {
//        LOG(__PRETTY_FUNCTION__," ",msg->addressPattern(), msg->arg());
        if(msg->arg().isStr()){
            std::string s;
            msg->arg().popStr(s);
            LOG(s);
        }
    }
}

void BufferReader::handleMessage(const BufferMessage& _msg)
{
    LOG(__PRETTY_FUNCTION__);
    std::unique_ptr<oscpkt::PacketReader> ptrPacketReader(new oscpkt::PacketReader);

    ptrPacketReader->init(_msg.buffer.data(),_msg.howMany);

    std::thread t(&BufferReader::processBuffer, this, std::move(ptrPacketReader));
    t.detach();
}
