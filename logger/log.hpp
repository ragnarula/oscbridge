#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <mutex>
#include <sstream>
#include "log_policy.h"


namespace logging {

enum severity_type
{
   debug = 1,
   error,
   warning
};

template< typename log_policy_type >
class logger
{
    unsigned log_line_number;
    std::string get_time();
    std::string get_logline_header();
    std::stringstream log_stream;
    std::unique_ptr<log_policy_type> policy;
    std::mutex write_mutex;

    //Core printing functionality
    void print_impl();
    template<typename First, typename...Rest>
    void print_impl(First parm1, Rest...parm);
public:
    logger( const std::string& name );

    template< severity_type severity , typename...Args >
    void print( Args...args );

    ~logger();
};

template< typename log_policy_type >
logger< log_policy_type >::logger( const std::string& name ) : policy( new log_policy_type )
{
   log_line_number = 0;
   if( !policy )
    {
       throw std::runtime_error("LOGGER: Unable to create the logger instance");
    }
    policy->setup( name );
}

template< typename log_policy_type >
logger< log_policy_type >::~logger()
{
    if( policy )
    {
       policy->teardown();
    }
}

template< typename log_policy_type >
std::string logger< log_policy_type >::get_time()
{
    std::string time_str;
    time_t raw_time;
    time( & raw_time );
    time_str = ctime( &raw_time );
    //without the newline character
    return time_str.substr( 0 , time_str.size() - 1 );
}

template< typename log_policy_type >
std::string logger< log_policy_type >::get_logline_header()
{
    std::stringstream header;
    header.str("");
    header.fill('0');
    header.width(7);
    header << log_line_number++ <<" < "<<get_time()<<" - ";
    header.fill('0');
    header.width(7);
    header <<clock()<<" > ~ ";
    return header.str();
}

template< typename log_policy_type >
    template< severity_type severity , typename...Args >
void logger< log_policy_type >::print( Args...args )
{
    write_mutex.lock();
    switch( severity )
    {
        case severity_type::debug:
             log_stream<<"<DEBUG> :";
             break;
        case severity_type::warning:
             log_stream<<"<WARNING> :";
             break;
        case severity_type::error:
             log_stream<<"<ERROR> :";
             break;
    };
    print_impl( args... );
    write_mutex.unlock();
}

template< typename log_policy_type >
void logger< log_policy_type >::print_impl()
{
    policy->write( get_logline_header() + log_stream.str() );
    log_stream.str("");
}

template< typename log_policy_type >
    template<typename First, typename...Rest >
void logger< log_policy_type >::print_impl(First parm1, Rest...parm)
{
    log_stream<<parm1;
    print_impl(parm...);
}

} //namespace logging
#endif // LOG_HPP
