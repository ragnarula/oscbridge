#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>
#include <QString>
#include "globals.h"
#include "mainwindow.h"

namespace Ui {
class AddDeviceDialog;
}

class AddDeviceDialog : public QDialog
{
    Q_OBJECT
    friend class MainWindow;

public:
    explicit AddDeviceDialog(QWidget *parent = 0);
    ~AddDeviceDialog();

private:
    Ui::AddDeviceDialog *ui;
    std::string name();
    std::string host();
    int port();

public slots:
private slots:
    void nameChanged(const QString&);
    void nameAvailable(bool);
signals:
    void checkName(const QString&);
};

#endif // ADDDEVICEDIALOG_H
