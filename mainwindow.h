#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include"dialog.h"
#include"Cartes.h"
#include"Jeu.h"
#include<QLabel>
#include<QPixmap>
#include<QLabel>
#include<QtGlobal>
#include"Cartes.h"
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QTimer>



QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    void onPageChanged(int);


private slots:
    void on_pushButton_clicked();

    void on_seconnecter_clicked();

    void on_retour_clicked();

    void on_annuler_clicked();

    void on_commentjouer_clicked();

    void on_next_clicked();

    void on_jouer_clicked();

    void on_retour2_clicked();



private:

    Ui::mainwindow *ui;

    Dialog *ptrconfig;

    QLabel *paquet;

    Cartes cartes[40];

    Jeu *monWidget;

    QVector <QLabel*> cartesLabels;

    QPixmap dos;

};



#endif // MAINWINDOW_H
