#ifndef LOG_POLICY_H
#define LOG_POLICY_H

#include <iostream>
#include <memory>
#include "debugwindow.h"

namespace logging {

class log_policy_interface
{
       public:
       virtual void     open_ostream(const std::string& name) = 0;
       virtual void     close_ostream() = 0;
       virtual void     write(const std::string& msg) = 0;
};

class file_log_policy : public log_policy_interface
{
       std::unique_ptr<std::ofstream > out_stream;
    public:
        file_log_policy();
        void open_ostream(const std::string& name);
        void close_ostream();
        void write(const std::string& msg);
        virtual ~file_log_policy();
};

class window_log_policy : public log_policy_interface
{
       std::unique_ptr<DebugWindow > dw;
    public:
        window_log_policy();
        void open_ostream(const std::string& name);
        void close_ostream();
        void write(const std::string& msg);
        virtual ~window_log_policy();
};

} //namespace logging
#endif // LOG_POLICY_H
