#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(0,2)
{
    LOG(__PRETTY_FUNCTION__);
    ui->setupUi(this);

    QObject::connect(ui->startButton, SIGNAL(clicked()),
            this, SLOT(startServer()));
    QObject::connect(ui->stopButton, SIGNAL(clicked()),
            this, SLOT(stopServer()));
    QObject::connect(ui->addButton, SIGNAL(clicked()),
            this, SLOT(addDevice()));
    QObject::connect(ui->removeButton, SIGNAL(clicked()),
            this, SLOT(removeDevice()));
    QObject::connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(connectDevice()));
    QObject::connect(ui->disconnectButton, SIGNAL(clicked()),
            this, SLOT(disconnectDevice()));
    QObject::connect(this, SIGNAL(onSetServerStatusLabel(QString)),
            ui->statusLabel, SLOT(setText(QString)));


    ui->deviceView->setModel(&model);
    model.setHorizontalHeaderItem(0, new QStandardItem ("Name"));
    model.setHorizontalHeaderItem(1, new QStandardItem ("Status"));
    ui->deviceView->verticalHeader()->setVisible(false);
}

MainWindow::~MainWindow()
{
    LOG(__PRETTY_FUNCTION__);
    delete ui;
}

//private slots
void MainWindow::startServer()
{
    LOG(__PRETTY_FUNCTION__);
    emit startButtonPushed(ui->portSpinBox->value());
}

void MainWindow::stopServer()
{
    LOG(__PRETTY_FUNCTION__);
    emit stopButtonPushed();
}

void MainWindow::addDevice()
{
    LOG(__PRETTY_FUNCTION__);
    AddDeviceDialog dialog;

    QObject::connect(&dialog, SIGNAL(checkName(QString)),
            this, SLOT(checkName(QString)));

    QObject::connect(this, SIGNAL(isNameAvailable(bool)),
            &dialog, SLOT(nameAvailable(bool)));

    if(dialog.exec() == AddDeviceDialog::Accepted){
        emit addDialogSuccessfull(dialog.name(), dialog.host(), dialog.port());
    }
}

void MainWindow::removeDevice()
{
    LOG(__PRETTY_FUNCTION__);
    QModelIndexList indexes = ui->deviceView->selectionModel()->selection().indexes();
    for(int i = 0; i < indexes.count(); ++i){
        QModelIndex index = indexes.at(i);
        QStandardItem *item = model.item(index.row());
        emit removeButtonPushed(item->text().toLocal8Bit().data());
    }
}

void MainWindow::checkName(const QString &_name)
{
    LOG(__PRETTY_FUNCTION__);
    emit checkName(_name.toLocal8Bit().data());
}

void MainWindow::nameAvailable(bool available)
{
    LOG(__PRETTY_FUNCTION__);
    emit isNameAvailable(available);
}

void MainWindow::connectDevice()
{
    LOG(__PRETTY_FUNCTION__);
    QModelIndexList indexes = ui->deviceView->selectionModel()->selection().indexes();
    for(int i = 0; i < indexes.count(); ++i){
        QModelIndex index = indexes.at(i);
        QStandardItem *item = model.item(index.row());
        emit connect(item->text().toLocal8Bit().data());
    }
}

void MainWindow::disconnectDevice()
{
    LOG(__PRETTY_FUNCTION__);
    QModelIndexList indexes = ui->deviceView->selectionModel()->selection().indexes();
    for(int i = 0; i < indexes.count(); ++i){
        QModelIndex index = indexes.at(i);
        QStandardItem *item = model.item(index.row());
        emit disconnect(item->text().toLocal8Bit().data());
    }
}

//public slots
void MainWindow::setServerStatusLabel(const char *_label)
{
    LOG(__PRETTY_FUNCTION__,_label);
    emit onSetServerStatusLabel(QString(_label));
}

void MainWindow::deviceAdded(const char *_name, const char *_status)
{
    LOG(__PRETTY_FUNCTION__,_name,_status);

    QStandardItem *name = new QStandardItem(_name);
    QStandardItem *status = new QStandardItem(_status);
    model.appendRow(QList< QStandardItem* >() << name << status);
}

void MainWindow::deviceRemoved(const char* _name)
{
    LOG(__PRETTY_FUNCTION__,_name);
    QList<QStandardItem *> items = model.findItems(_name, Qt::MatchExactly, 0);
    QModelIndex index = items[0]->index();
    model.removeRow(index.row());
}

void MainWindow::updateDevice(const char* _name, const char* _status)
{
    LOG(__PRETTY_FUNCTION__,_name,_status);
    QList<QStandardItem *> items = model.findItems(_name, Qt::MatchExactly, 0);
    QModelIndex index = items[0]->index();
    QStandardItem *item = model.item(index.row(),1);
    item->setText(_status);
}

