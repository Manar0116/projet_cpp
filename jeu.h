#ifndef JEU_H
#define JEU_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QtGlobal>
#include "Cartes.h"
#include <QList>
#include <ctime>
#include<QRandomGenerator>
#include <QTimer>
#include<QMouseEvent>
#include <iterator>
#include <vector>


namespace Ui {
class Jeu;
}

class Jeu : public QWidget
{
    Q_OBJECT

public:

    explicit Jeu(QWidget *parent = nullptr);
    ~Jeu();
    void initialiserjeu();
    void afficherCartesSelectionnees();

    void carteJouee();

    void comparerCartes();
    void traiterClicJoueur1(QLabel *carte);
    void traiterClicJoueur2(QLabel *carte);

    Cartes cartes[40];



  private:
    Ui::Jeu *ui;
    QLabel *paquet;
    QLabel *labelcarte;

    bool distributionTerminee;
    int delayBetweenCards;
    bool distributionEnCours = false;
    bool boutonActif = true;

    // Structure pour représenter une carte avec son index et le QLabel associé
    struct CarteJoueur {
        int index;
        QLabel *label;
    };

    QVector<Jeu::CarteJoueur> getJoueur2Cartes() const;
    // Vecteurs pour stocker les cartes des joueurs
    QVector<CarteJoueur> joueur1Cartes;
    QVector<CarteJoueur> joueur2Cartes;
    QVector<CarteJoueur> cartesSelectionneesJoueur1;
    QVector<CarteJoueur> cartesSelectionneesJoueur2;


    int joueur1Score ;
    int joueur2Score ;


    QLabel *labelScoreJoueur1;
    QLabel *labelScoreJoueur2;



protected:
    bool eventFilter(QObject *obj,QEvent *event)override;


private slots :
    void afficherCarteChoisie(QLabel *labelJoueur, int index);

signals:
    void signalRejouerClicked();

};

#endif // JEU_H
