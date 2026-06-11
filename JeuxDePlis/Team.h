#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "PaquetCarte.h"
#include "Joueur.h"

using namespace std;

class Team
{
private:
    string teamNom;
    int pointManche;
    int nbPoint;
    vector<PaquetCarte> plisGagne;
    vector<shared_ptr<Joueur>> joueurs;

public:
    Team();

    Team(string nomTeam);

    void clearPlis();

    void addPlisGagne(PaquetCarte&  plis);

    // on copie pas inutilement le string (on le prend par réfernce)
    void setTeamNom(const string& nom);

    string getTeamNom();

    void setPointManche(int nb);

    int getPointManche();

    void setNbPoint(int nb);

    int getNbPoint();

    // on renvoie l'adresse du vecteur de pointeurs (pour éviter de le recopier inutillement)
    const vector<PaquetCarte>& getPlisGagne() const;

    void setJoueurs(vector<shared_ptr<Joueur>> joueurs);

    const vector<shared_ptr<Joueur>>& getJoueurs() const;
};

#endif


