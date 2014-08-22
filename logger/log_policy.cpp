#include "log_policy.h"
#include <string>
#include <exception>
#include <fstream>
#include "debugwindow.h"

using namespace logging;
file_log_policy::file_log_policy() : out_stream( new std::ofstream ) {}

void file_log_policy::setup(const std::string& name)
{
   out_stream->open( name.c_str(), std::ios_base::binary|std::ios_base::out );
   if( !out_stream->is_open() )
   {
        throw(std::runtime_error("LOGGER: Unable to open an output stream"));
   }
}

void file_log_policy::teardown()
{
    if( out_stream )
    {
        out_stream->close();
    }
}

void file_log_policy::write(const std::string& msg)
{
    (*out_stream)<<msg<<std::endl;
}

file_log_policy::~file_log_policy()
{
    if( out_stream )
    {
        teardown();
    }
}

window_log_policy::window_log_policy() {}

void window_log_policy::setup(const std::string& name)
{
   (void)name;


}

void window_log_policy::teardown()
{

}

void window_log_policy::write(const std::string& msg)
{

    if(!dw){
        dw.reset(new DebugWindow);
    }
    dw->show();
    dw->append(QString::fromStdString(msg));
}

window_log_policy::~window_log_policy(){};

