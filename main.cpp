#include "globals.h"

#include "mainwindow.h"
#include <QApplication>
#include "apppaths.h"
#include <memory>
#include "core.h"

LOG_INIT

int main(int argc, char *argv[])
{
    LOG_INST.register_policy(std::shared_ptr<logging::file_log_policy>(
                                 new logging::file_log_policy(AppPaths::get_app_bundle_path()+"/execution.log")));
    QApplication a(argc, argv);
    Core core;
    MainWindow w;

    QObject::connect(&w,SIGNAL(startButtonPushed(const uint16_t&)),
                     &core, SLOT(startServer(const uint16_t&)));
    QObject::connect(&w, SIGNAL(stopButtonPushed()),
                     &core, SLOT(stopServer()));
    QObject::connect(&core, SIGNAL(serverStatusChanged(const char*)),
                     &w, SLOT(setServerStatusLabel(const char*)));

    w.show();

    return a.exec();
}
