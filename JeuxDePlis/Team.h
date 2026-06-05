// Team.h
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
    vector<unique_ptr<PaquetCarte>> plisGagne;
    int pointManche;
    int nbPoint;
    char teamNom;
    vector<shared_ptr<Joueur>> joueurs;

public:
    void clearPlis();
    void setPlisGagne(unique_ptr<PaquetCarte> plis);
    PaquetCarte* getPlisGagne();
    void setPointManche(int nb);
    int getPointManche();
    void setNbPoint(int nb);
    int getNbPoint();
    void setTeamNom(char nom);
    char getTeamNom();
    void setJoueurs(vector<shared_ptr<Joueur>> joueurs);
    vector<shared_ptr<Joueur>> getJoueurs();
};

#endif

