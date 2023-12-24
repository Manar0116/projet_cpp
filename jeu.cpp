#include "jeu.h"
#include "ui_jeu.h"
#include "Cartes.h"
#include"mainwindow.h"
#include<cstdlib>
#include <QMessageBox>

#include <QCoreApplication>
#include <QMouseEvent>
#include<QDebug>


Jeu::Jeu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Jeu)

{
    ui->setupUi(this);
    initialiserjeu();

    // délai
    delayBetweenCards ;


    // Initialisation des scores
    int joueur1Score = 0;
    int joueur2Score = 0;

    // Initialisation des QLabel pour afficher le score
    ui->labelScoreJoueur1->setText(QString("Score: ") + QString::number(joueur1Score));
    ui->labelScoreJoueur2->setText(QString("Score: ") + QString::number(joueur2Score));



}
Jeu::~Jeu()
{
    delete ui;
}

void Jeu::initialiserjeu(){

    // Définir un tableau de valeurs spécifiques pour chaque carte
    int valeurs[] = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12};

    // Charger les images et les attribuer aux objets Cartes
    for (int i = 0; i < 40; ++i)
    {
        QString cheminFaceVisible = QString(":imgcarte/%1.gif").arg(i, 2, 10, QChar('0'));
        QString cheminDos = ":/imgcarte/backcard.jpg";

        QPixmap faceVisible(cheminFaceVisible);
        QPixmap dos(cheminDos);

        // condition qui vérifie si les objets QPixmap faceVisible et dos ont été correctement chargés avec des images non nulles
        if (!faceVisible.isNull() && !dos.isNull() && i < sizeof(valeurs) / sizeof(valeurs[0]))
        {
            cartes[i].definirImages(faceVisible, dos);
            cartes[i].definirValeur(valeurs[i]);
        }
    }



    // Mettre à jour l'interface graphique pour montrer le dos des cartes dans le label
    QPixmap dos(":/imgcarte/backcard.jpg");

    // Afficher le paquet de cartes dans le label
    for (int i = 0; i < 40; ++i)
    {
        QLabel *carteLabel = new QLabel(ui->paquet);
        carteLabel->setPixmap(dos.scaled(140, 170, Qt::KeepAspectRatio));
        carteLabel->move(i * (0.6), i * (0.5)); // Décalage pour superposer les cartes
        carteLabel->setMouseTracking(true);
        carteLabel->installEventFilter(this);
        carteLabel->show();
    }

    //melanger les cartes
    QRandomGenerator random;
    std::random_shuffle(std::begin(cartes), std::end(cartes), [&random](int n) { return random.bounded(n); });



    // un QTimer pour déclencher la distribution après un délai
    QTimer::singleShot(3000, this, [=]() {

        int delayBetweenCards = 500;


        QMessageBox msgBox;
        msgBox.setWindowTitle("Début de la distribution");
            msgBox.setText("Attendez que la distribution se termine, puis cliquez sur votre carte. "
                           "À chaque fois que vous jouez votre tour, attendez que l'ordinateur joue, "
                           "et après recliquez sur votre carte");

            // Appliquer une feuille de style CSS pour changer la couleur du texte
            msgBox.setStyleSheet("QMessageBox { background-color: lightblue; }"
                                 "QMessageBox QLabel { color: black; font-size: 16pt; border-radius:12px }");

        msgBox.exec();

        // Mélanger l'ordre des cartes a chaque foisqu'ils sont ditribués
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(cartes), std::end(cartes), g);


            // Distribuer les 20 premières cartes au premier QLabel
            for (int i = 0; i < 20; ++i)
            {
                QTimer::singleShot(i * delayBetweenCards, this, [=]() {
                    CarteJoueur carteJoueur;
                    carteJoueur.index = i;
                    carteJoueur.label = new QLabel(ui->labelJoueur1);
                    carteJoueur.label->setPixmap(cartes[i].getImage().scaled(140, 170, Qt::KeepAspectRatio));
                    carteJoueur.label->move(i * (0.6), i * (0.5));
                    carteJoueur.label->setMouseTracking(true);
                    carteJoueur.label->installEventFilter(this);
                    carteJoueur.label->show();

                    joueur1Cartes.append(carteJoueur);
                });
            }


           // Distribuer les 20 cartes restantes au deuxième QLabel
           for (int i = 20; i < 40; ++i)
           {
            QTimer::singleShot((i - 20) * delayBetweenCards, this, [=]() {
                    CarteJoueur carteJoueur;
                    carteJoueur.index = i;
                    carteJoueur.label = new QLabel(ui->labelJoueur2);
                    carteJoueur.label->setPixmap(cartes[i].getImage().scaled(140, 170, Qt::KeepAspectRatio));
                    carteJoueur.label->move((i - 20) * (0.6), (i - 20) * (0.5));
                    carteJoueur.label->setMouseTracking(true);
                    carteJoueur.label->installEventFilter(this);
                    carteJoueur.label->show();

                    joueur2Cartes.append(carteJoueur);
                });
           }

        // Cacher les cartes dans le label "paquet"
        QTimer::singleShot(20 * delayBetweenCards, this, [=]() {
        QList<QLabel *> paquetLabels = ui->paquet->findChildren<QLabel *>();
        for (QLabel *label : paquetLabels)
        {
            label->hide();
        }
        });

    });

}

//l'affichage visuel d'une carte choisie dans l'interface
void Jeu::afficherCarteChoisie(QLabel *labelJoueur, int index )
{

    // s'assurer que CoteVisible est défini sur true pour afficher la face visible
    cartes[index].setCoteVisible(true);

    // Si CoteVisible est vrai, getImage() renverra la face visible, sinon le dos
    QPixmap imageCarte = cartes[index].getImage();

    // un QLabel pour afficher la carte choisie
    QLabel *carteChoisieLabel = new QLabel(labelJoueur);
    carteChoisieLabel->setPixmap(imageCarte.scaled(140, 170, Qt::KeepAspectRatio));
    carteChoisieLabel->move((index) * (0.6), (index) * (0.5));
    carteChoisieLabel->setMouseTracking(true);
    carteChoisieLabel->show();
}
void Jeu::afficherCartesSelectionnees()
{
    // Parcourir toutes les cartes sélectionnées du Joueur 1
    for (const CarteJoueur &carte : cartesSelectionneesJoueur1) {
        // Afficher la carte choisie dans l'emplacement spécifié pour le Joueur 1
        afficherCarteChoisie(ui->place1, carte.index);
    }

    for (const CarteJoueur &carte : cartesSelectionneesJoueur2) {
        afficherCarteChoisie(ui->place2, carte.index);
    }

}



// Filtre d'événements pour détecter les clics sur les cartes
bool Jeu::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress ) {
        // Lorsqu'une carte est cliquée, la déplacer vers le parent correspondant
        QLabel *carte = qobject_cast<QLabel *>(obj);

        if (carte) {
            QWidget *parentWidget = carte->parentWidget();
            if (parentWidget == ui->labelJoueur1) {

                traiterClicJoueur1(carte);


                // Changer de tour après le tour de l'ordinateur

                QTimer::singleShot(1500, this, [this, carte]() {
                    if (!ui->labelJoueur2->children().isEmpty()) {

                        traiterClicJoueur2(carte);
                        // Comparer les cartes immédiatement après la sélection
                        comparerCartes();
                    }

                });
            }

        }

    }

    // Laisser l'objet de base traiter l'événement
    return QWidget::eventFilter(obj, event);
}




// Fonction pour le traitement du joueur 1
void Jeu::traiterClicJoueur1(QLabel *carte) {
    // Obtenir l'index de la carte cliquée dans la liste des enfants du label du Joueur 1
    int index1 = ui->labelJoueur1->children().indexOf(carte);

    if (index1 != -1) {
        // Déplacer la carte vers l'emplacement spécifié pour le Joueur 1
        joueur1Cartes[index1].label->setParent(ui->place1);
        // Afficher visuellement la carte choisie dans cet emplacement
        afficherCarteChoisie(ui->place1, joueur1Cartes[index1].index);
        // Ajouter la carte à la liste des cartes sélectionnées du Joueur 1
        cartesSelectionneesJoueur1.append(joueur1Cartes[index1]);
        // Retirer la carte de la liste des cartes du Joueur 1
        joueur1Cartes.removeAt(index1);
    }

}

// Fonction pour le traitement du joueur 2
void Jeu::traiterClicJoueur2(QLabel *carte) {
    QLabel *carteJoueur2 = qobject_cast<QLabel *>(ui->labelJoueur2->children().last());

    int index2 = ui->labelJoueur2->children().indexOf(carteJoueur2);
    if (index2 != -1) {
        joueur2Cartes[index2].label->setParent(ui->place2);
        afficherCarteChoisie(ui->place2, joueur2Cartes[index2].index);
        cartesSelectionneesJoueur2.append(joueur2Cartes[index2]);
        joueur2Cartes.removeAt(index2);


    }
}
void Jeu::comparerCartes() {

    if (!cartesSelectionneesJoueur1.isEmpty() && !cartesSelectionneesJoueur2.isEmpty()) {
        // Comparer les valeurs des cartes sélectionnées
        int valeurJoueur1 = cartes[cartesSelectionneesJoueur1.last().index].obtenirValeur();
        int valeurJoueur2 = cartes[cartesSelectionneesJoueur2.last().index].obtenirValeur();

        //les règles du jeu
        if (valeurJoueur1 > valeurJoueur2) {
            // Joueur 1 gagne

            joueur1Score += 1;
        //afficher le score pour joueur1
            ui->labelScoreJoueur1->setText(QString("Score: ") + QString::number(joueur1Score));


        } else if (valeurJoueur1 < valeurJoueur2) {
            // Joueur 2 gagne         
            joueur2Score += 1;
            ui->labelScoreJoueur2->setText(QString("Score: ") + QString::number(joueur2Score));

        }else{

        //n'ajouer rien si les cartes sont de la meme valeur

        }

        cartesSelectionneesJoueur1.last().label->hide();
        cartesSelectionneesJoueur2.last().label->hide();

        // Effacer les listes de cartes sélectionnées pour le prochain tour
        cartesSelectionneesJoueur1.clear();
        cartesSelectionneesJoueur2.clear();}


        // Vérifiez si toutes les cartes ont été jouées
        if (joueur1Cartes.isEmpty() && joueur2Cartes.isEmpty()) {
        // Affichez le gagnant dans une boîte de dialogue
        QString message;
        if (joueur1Score > joueur2Score) {
            message = "vous avez gagné partie avec un score de " + QString::number(joueur1Score);
        } else if (joueur1Score < joueur2Score) {
            message = "IA a gagné la partie avec un score de " + QString::number(joueur2Score)+",à la prochaine";
        } else {
            message = "La partie se termine par une égalité";
        }

       //utilisation de css pour modifier cette boîte de dialogue
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fin de la partie");
        msgBox.setText(message);

        // Appliquer une feuille de style CSS pour changer la couleur
        msgBox.setStyleSheet("QMessageBox { background-color: lightblue; }"
                             "QMessageBox QLabel { color: black; font-size: 16pt; }");

        msgBox.exec();
    }
}


