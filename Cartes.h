#ifndef CARTES_H
#define CARTES_H

#include <QPixmap>
#include <QMainWindow>

class Cartes
{
public:
    Cartes();
    void definirImages(const QPixmap &faceVisible, const QPixmap &dos);
    QPixmap getImage() const;
    void definirValeur(int valeur);
    int obtenirValeur() const; // méthode pour obtenir la valeur de la carte
    void afficherDos(); // Méthode pour afficher la face cachée
    void setCoteVisible(bool visible);


private:
    QPixmap faceVisible;
    QPixmap dos;
    bool CoteVisible;  // Indicateur pour savoir si la face visible est actuellement affichée
    int valeur;
    QPixmap imageFaceVisible;
};

#endif // CARTES_H
