#include <QApplication>
#include <iostream>
#include <memory>
#include <string>
#include "adddevicedialog.h"
#include "apppaths.h"
#include "core.h"
#include "globals.h"
#include "mainwindow.h"

LOG_INIT

int main(int argc, char *argv[])
{
    LOG_INST.register_policy(std::shared_ptr<logging::file_log_policy>(
                                 new logging::file_log_policy(AppPaths::get_app_bundle_path()+"/execution.log")));
    QApplication a(argc, argv);
    Core core;
    MainWindow w;
    //window -> core
    QObject::connect(&w,SIGNAL(startButtonPushed(const uint16_t&)),
                     &core, SLOT(startServer(const uint16_t&)));
    QObject::connect(&w, SIGNAL(stopButtonPushed()),
                     &core, SLOT(stopServer()));
    QObject::connect(&w, SIGNAL(addDialogSuccessfull(const std::string&,const std::string&,int)),
                     &core, SLOT(addDevice(const std::string&,const std::string&,int)));
    QObject::connect(&w, SIGNAL(removeButtonPushed(const char*)),
                     &core, SLOT(removeDevice(const char*)));
    QObject::connect(&w, SIGNAL(checkName(const char*)),
                     &core, SLOT(checkName(const char*)));
    QObject::connect(&w, SIGNAL(connect(const char*)),
                     &core, SLOT(connect(const char*)));
    QObject::connect(&w, SIGNAL(disconnect(const char*)),
                     &core, SLOT(disconnect(const char*)));
    //core -> window
    QObject::connect(&core, SIGNAL(serverStatusChanged(const char*)),
                     &w, SLOT(setServerStatusLabel(const char*)));
    QObject::connect(&core, SIGNAL(deviceAdded(const char*,const char*)),
                     &w, SLOT(deviceAdded(const char*,const char*)));
    QObject::connect(&core, SIGNAL(deviceRemoved(const char*)),
                     &w, SLOT(deviceRemoved(const char*)));
    QObject::connect(&core, SIGNAL(deviceStateChanged(const char*,const char*)),
                     &w, SLOT(updateDevice(const char*,const char*)));
    QObject::connect(&core, SIGNAL(isNameAvailable(bool)),
                     &w, SLOT(nameAvailable(bool)));


    w.show();
    return a.exec();

}
