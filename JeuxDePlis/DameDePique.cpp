#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Team.h"
#include "DameDePique.h"
#include "TableJeu.h"


DameDePique::DameDePique() {
	Jeu::setJeuCourant(this);
	nbJoueurs = 4;
	nbManche = 0;
	Coeur_Brise = false;
	pointsGagnant = 100;
}

void DameDePique::creerPaquetJeu() {
	for (const string& newcouleur : Couleur) {
		for (const string& newvaleur : ordreCarte) {
			unique_ptr<Carte> newcarte = make_unique<Carte>();
			newcarte->setCouleur(newcouleur);
			newcarte->setValeur(newvaleur);
			getPaquetJeu().addCarte(move(newcarte));
		}
	}
}


void DameDePique::distribuer() {
	int i = 0;

	while (getPaquetJeu().PaquetSize() > 0) {
		getPaquetJeu().giveCard(0, getJoueurById(i)->getMain());
		i = (i + 1) % getNbJoueurs();
	}

}

bool DameDePique::checkCoeurBrise() { 
	return Coeur_Brise; 
}

bool DameDePique::checkWin() {
	for (size_t i = 0; i < getNbEquipe(); i++) {
		if (getTeam()[i]->getNbPoint() >= getPointsGagnant()) {
			cout << "L'équipe " << getTeam()[i]->getTeamNom() << " a gagné !" << endl;
			return true;
		}
	}
	return false;
}

int DameDePique::gagnantPlis() {
	string firstCouleur = "null";
	TableJeu& table = getTable();
	PaquetCarte& plis = table.getPlis();
	int idFirstJoueur = table.getIdPremierJoueur();
	int idgagnant = idFirstJoueur;
	string valeurgagnant = "null";
	for (int i = 0; i < getNbJoueurs(); i++)
	{
		const auto& carte = plis.getListeCartePaquet()[i];
		if ( firstCouleur == "null") {
			firstCouleur = carte->getCouleur();
			valeurgagnant = carte->getValeur();
		}    
		else if (carte->getCouleur() == firstCouleur) {
			if (CompareCarte(carte, plis.getListeCartePaquet()[idgagnant])) {
				idgagnant = i;
				valeurgagnant = carte->getValeur();
			}
		}


	}
	table.setIdPremierJoueur(idgagnant);
	return 0;
}
list<int> DameDePique::carteValide(const PaquetCarte& main, const PaquetCarte& plis) {
	list<int> carteValide;
	if (plis.PaquetSize() == 0) {
		if (checkCoeurBrise()) {
			int index = 0;
			for (const auto& carte : main.getListeCartePaquet()) {
				carteValide.push_back(index);
				index++;
			}
		}
		else {
			int index = 0;
			for (const auto& carte : main.getListeCartePaquet()) {
				if (carte->getCouleur() != "Coeur") {
					carteValide.push_back(index);
				}
				index++;
			
			}
		}
	}
	else {
		Carte firstCartePlis = *plis.getListeCartePaquet()[0];
		if (firstCartePlis.checkCouleurPlisDansMain(main))
		{
			string firstCouleur = plis.getListeCartePaquet()[0]->getCouleur();
			for (int i = 0; i < main.PaquetSize(); i++)
			{
				if (main.getListeCartePaquet()[i]->getCouleur() == firstCouleur) {
					carteValide.push_back(i);
				}
			}
		}
		if (!firstCartePlis.checkCouleurPlisDansMain(main)) {
			for (int i = 0; i < main.PaquetSize(); i++)
			{
				carteValide.push_back(i);
			}
		}
	}
	return carteValide;
}
const int DameDePique::playFirst() {
	TableJeu* table = &getTable();
	if (getJoueurById(0)->getMain().PaquetSize() == 13) {
		for (int i=0; i<getNbJoueurs(); i++)
		{
			const auto& cartes = getJoueurById(i)->getMain().getListeCartePaquet();

			for (const auto& carte : cartes)
			{
				if (carte->getValeur() == "2" &&
					carte->getCouleur() == "Trefle")
				{
					table->setIdPremierJoueur(i);
					return i;
				}
			}
		}

	}
	else {
		int premierJoueur = table->getIdPremierJoueur();
		return premierJoueur;
	}
	return 0;
}
const int DameDePique::playNext() {
	int idgagnant = gagnantPlis();
	return idgagnant;
}

void DameDePique::compterPoint() {
	for (int i = 0; i < getNbJoueurs(); i++)
	{
		const auto& plis = getTeam()[i]->getPlisGagne();
		int pointEquipe = 0;
		for (const auto& pli : plis)
		{
			const auto& cartes = pli.getListeCartePaquet();

			for (const auto& carte : cartes)
			{
				if (carte->getCouleur() == "Coeur")
				{
					pointEquipe += 1;
				}
				else if (carte->getCouleur() == "Pique" && carte->getValeur() == "Dame")
				{
					pointEquipe += 13;
			
				
				}
			}
		}
		if (pointEquipe == 26) {
			pointEquipe = 0;
			for (int j = 0; j < getNbEquipe(); j++)
			{
				if (j != i) {
					getTeam()[j]->setNbPoint(
						getTeam()[j]->getNbPoint() + 26);
				}
			}
		}
		getTeam()[i]->setNbPoint(
			getTeam()[i]->getNbPoint() + pointEquipe);
	}
}

void DameDePique::jouer() {
	TableJeu* table = &getTable();
	creerPaquetJeu();
	while (!checkWin()) {
		distribuer();
		int nbManche = getNbManche();
		while (getJoueurById(0)->getMain().PaquetSize() > 0) {
			for (int i = 0; i < getNbJoueurs(); i++) {
				getJoueurById(0)->jouerCoup();
			}
			int idgagnantplis=gagnantPlis();
			Team* equipeGagnante = nullptr;
			for (int i = 0; i < getNbEquipe(); i++) {
				const auto& joueursEquipe = getTeam()[i]->getJoueurs();
				for (const auto& joueur : joueursEquipe) {
					if (joueur->getIdjoueur() == idgagnantplis) {
						equipeGagnante = getTeam()[i];
						break;
					}
				}
			}
			PaquetCarte& plisGagne = table->getPlis();
			equipeGagnante->addPlisGagne(plisGagne);
		
		}
		compterPoint();
		for (int i = 0; i < getNbEquipe(); i++) {
			getTeam()[i]->clearPlis();
		}
		creerPaquetJeu();
	}
}