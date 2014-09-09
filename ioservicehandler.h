//Class to handle the main io_Service for the program and
//provide the main threads that will be calling run

#ifndef IOSERVICEHANDLER_H
#define IOSERVICEHANDLER_H

#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <set>
#include <thread>
#include "globals.h"

class IOServiceHandler
{
    // Shared pointer to io_service. Other classes may need to access, hence shared.
    std::shared_ptr<boost::asio::io_service> ptrIo;
    // Vector to hold threads calling io_service.run();
    std::vector<std::thread> threadPool;
    // Number of threads to call run();
    std::size_t numThreads;
    // Work to keep io_service running
    std::unique_ptr<boost::asio::io_service::work> work;
    //calls io service run
    void runThread();
public:
    IOServiceHandler(std::size_t);
    // Start thread pool
    void start();
    // Stop thread pool
    void stop();
    // get shared ptr to io_service
    std::shared_ptr<boost::asio::io_service> getIoService();
    // Destructor... calls stop()
    ~IOServiceHandler();
};

#endif // IOSERVICEHANDLER_H
