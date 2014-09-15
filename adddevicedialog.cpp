#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"

AddDeviceDialog::AddDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDeviceDialog)
{
    LOG(__PRETTY_FUNCTION__);
    ui->setupUi(this);
    connect(ui->nameEdit, SIGNAL(textChanged(const QString&)),
            this, SLOT(nameChanged(const QString&)));
    ui->buttonBox->buttons().at(0)->setEnabled(false);
}

AddDeviceDialog::~AddDeviceDialog()
{
    LOG(__PRETTY_FUNCTION__);
    delete ui;
}

void AddDeviceDialog::nameChanged(const QString &_name)
{
    LOG(__PRETTY_FUNCTION__);
    emit checkName(_name);
}

void AddDeviceDialog::nameAvailable(bool available)
{
    LOG(__PRETTY_FUNCTION__);
    if(available){
        ui->nameTakenLabel->setText("Available");
        ui->buttonBox->buttons().at(0)->setEnabled(true);
    } else {
        ui->nameTakenLabel->setText("Not available");
        ui->buttonBox->buttons().at(0)->setEnabled(false);
    }
}

std::string AddDeviceDialog::name()
{
    LOG(__PRETTY_FUNCTION__);
    return ui->nameEdit->text().toStdString();
}

std::string AddDeviceDialog::host()
{
    LOG(__PRETTY_FUNCTION__);
    return ui->addressEdit->text().toStdString();
}

int AddDeviceDialog::port()
{
    LOG(__PRETTY_FUNCTION__);
    return ui->portEdit->value();
}
