// Team.cpp
#include "Team.h"

// constructeur par défaut de Team, instancie les attributs à 0
Team::Team() : pointManche(0), nbPoint(0), teamNom("") {}

// constructeur de confort avec le nom de l'équipe
Team::Team(string nomTeam) : pointManche(0), nbPoint(0), teamNom(nomTeam) {}

void Team::clearPlis() {
    this->plisGagne.clear();
}


void Team::addPlisGagne(PaquetCarte&  plis) {
    this->plisGagne.push_back(move(plis));
}

void Team::setTeamNom(const string& nom) {
    this->teamNom = nom;
}

string Team::getTeamNom() {
    return this->teamNom;
}

void Team::setPointManche(int nb) {
    this->pointManche = nb;
}

int Team::getPointManche() {
    return this->pointManche;
}

void Team::setNbPoint(int nb) {
    this->nbPoint = nb;
}

int Team::getNbPoint() {
    return this->nbPoint;
}

/*
La fonction retourne un pointeur brut sans transferer sa propriété pour consulter le vector "plisGagne"
*/
const vector<PaquetCarte>& Team::getPlisGagne() const {
    return this->plisGagne;
}

/*
on recoit le vecteur par valeur et on le move dans l'attribut "joueurs"
joueur est un shared_ptr qui devient propriétaire du vecteur sans devoir faire une copie inutile (il pointe vers 
le vector existant)
*/
void Team::setJoueurs(vector<shared_ptr<Joueur>> joueurs) {
    this->joueurs = move(joueurs);
}

// la méthode appelant renvoie "le vecteur pointeur partagé de joueur" par valeur
// retourner une référence const
const vector<shared_ptr<Joueur>>& Team::getJoueurs() const {
    return this->joueurs;
}
