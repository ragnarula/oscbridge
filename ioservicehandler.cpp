#include "ioservicehandler.h"

IOServiceHandler::IOServiceHandler(std::size_t _numThreads)
    : ptrIo(new boost::asio::io_service), numThreads(_numThreads)
{
    LOG(__PRETTY_FUNCTION__, " numThreads ", numThreads);
    start();
}

void IOServiceHandler::start()
{
    LOG(__PRETTY_FUNCTION__);
    // give some work to the io_service to prevent run() from returning
    work.reset(new boost::asio::io_service::work(*ptrIo));
    //create threads calling run()
    for(std::size_t i = 0; i < numThreads; i++){
        threadPool.push_back(std::thread/*(boost::bind*/(&IOServiceHandler::runThread, this))/*)*/;
    }
}

void IOServiceHandler::runThread()
{
    LOG(__PRETTY_FUNCTION__, " ", std::this_thread::get_id());
    ptrIo->run();
}

void IOServiceHandler::stop()
{
    LOG(__PRETTY_FUNCTION__);
    // Reset work so io_Service cal stop
    work.reset();
    // join all threads
    for(std::vector<std::thread>::iterator iter = threadPool.begin(); iter != threadPool.end(); iter++){
        LOG(__PRETTY_FUNCTION__," joined thread ",iter->get_id());
        iter->join();
    }
    threadPool.erase(threadPool.begin(),threadPool.end());
}

std::shared_ptr<boost::asio::io_service> IOServiceHandler::getIoService()
{
    LOG(__PRETTY_FUNCTION__);
    return ptrIo;
}

IOServiceHandler::~IOServiceHandler()
{
    LOG(__PRETTY_FUNCTION__);
    stop();
}
