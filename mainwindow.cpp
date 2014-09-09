#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked()),
            this, SLOT(startServer()));
    connect(ui->stopButton, SIGNAL(clicked()),
            this, SLOT(stopServer()));
    connect(this, SIGNAL(onSetServerStatusLabel(QString)),
            ui->statusLabel, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startServer()
{
    emit startButtonPushed(ui->portSpinBox->value());
}

void MainWindow::setServerStatusLabel(const char *_label)
{
    emit onSetServerStatusLabel(QString(_label));
}

void MainWindow::stopServer()
{
    emit stopButtonPushed();
}
