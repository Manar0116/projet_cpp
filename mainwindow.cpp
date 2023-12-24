#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "dialog.h"
#include "Cartes.h"
#include "Jeu.h"


mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainwindow)
{
    ui->setupUi(this);

//initialisation de la première page
    ui->stackedWidget->setCurrentIndex(0);

    ptrconfig = new Dialog(this);


    // Connectez le signal clicked du bouton au slot associé
    connect(ui->jouer, &QPushButton::clicked, this, &mainwindow::on_jouer_clicked);

}


mainwindow::~mainwindow()
{
    delete ui;
    delete ptrconfig;
}

void mainwindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainwindow::on_seconnecter_clicked()
{
    ptrconfig->show();
}

void mainwindow::on_retour_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex - 1);
}

void mainwindow::on_annuler_clicked()
{
    QApplication::quit();
}

void mainwindow::on_commentjouer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainwindow::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void mainwindow::on_jouer_clicked()

{


    Jeu *monWidget = new Jeu(this);

    monWidget->show();

}

void mainwindow::on_retour2_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex - 1);
}







