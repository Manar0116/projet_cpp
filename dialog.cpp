#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(500,500);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_enregister_clicked()
{
    QDialog::close();

}

