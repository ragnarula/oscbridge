#ifndef OSCADDRESSREADER_H
#define OSCADDRESSREADER_H

#include <string>
#include "oscpkt.hh"
#include "globals.h"


class OscAddressReader
{
    std::vector<std::string> addressParts;
    oscpkt::Message &msg;
    std::string blank;
    std::vector<std::string>::iterator popIter;

    void splitAddress(const std::string&);
public:
    OscAddressReader(oscpkt::Message&);
    std::string& get(uint32_t);
    std::string& pop();
    std::string& head();
};

#endif // OSCADDRESSREADER_H
