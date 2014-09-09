#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <memory>
#include "globals.h"
#include "ioservicehandler.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startServer();
    void stopServer();
public slots:
    void setServerStatusLabel(const char*);

signals:
    void startButtonPushed(const uint16_t&);
    void stopButtonPushed();
    void onSetServerStatusLabel(const QString &);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
