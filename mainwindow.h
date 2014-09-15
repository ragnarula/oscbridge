#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <cstdlib>
#include <memory>
#include "adddevicedialog.h"
#include "globals.h"
#include "ioservicehandler.h"
#include "ui_mainwindow.h"
#include "globals.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class AddDeviceDialog;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startServer();
    void stopServer();
    void addDevice();
    void removeDevice();

    void connectDevice();
    void disconnectDevice();

public slots:
    void setServerStatusLabel(const char*);
    void deviceAdded(const char*, const char*);
    void updateDevice(const char*,const char*);
    void deviceRemoved(const char*);

    //add dialog name check
    void checkName(const QString&);
    void nameAvailable(bool);

signals:
    void startButtonPushed(const uint16_t&);
    void stopButtonPushed();
    void addDialogSuccessfull(const std::string&, const std::string&, int);
    void removeButtonPushed(const char*);
    void onSetServerStatusLabel(const QString &);

    void checkName(const char*);
    void isNameAvailable(bool);

    void connect(const char*);
    void disconnect(const char*);

private:
    Ui::MainWindow *ui;
    QStandardItemModel model;
};

#endif // MAINWINDOW_H
