#include "Cartes.h"

Cartes::Cartes():CoteVisible(false) {


}
void Cartes::definirImages(const QPixmap &faceVisible, const QPixmap &dos) {
    this->faceVisible = faceVisible;
    this->dos = dos;
}

QPixmap Cartes::getImage() const {
    return CoteVisible ? faceVisible : dos;
}
void Cartes::definirValeur(int valeur) {
    this->valeur = valeur;
}
int Cartes::obtenirValeur() const {
    return valeur;
}
void Cartes::afficherDos()
{
    CoteVisible = false;
}

void Cartes::setCoteVisible(bool visible) {
    CoteVisible = visible;
}
