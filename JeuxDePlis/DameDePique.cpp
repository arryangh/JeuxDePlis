#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "Team.h"
#include "DameDePique.h"

DameDePique::DameDePique() {
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

void DameDePique::jouerCarte() {

}

void DameDePique::checkWin() {
	for (size_t i = 0; i < getNbEquipe(); i++) {
		if (getTeam()[i]->getNbPoint() >= getPointsGagnant()) {
			cout << "L'équipe " << getTeam()[i]->getTeamNom() << " a gagné !" << endl;
			exit(0);
		}
	}
}

int DameDePique::gagnantPlis() {
	int idgagnant = 0;
	string firstCouleur = "";
	TableJeu table;
	// on parcourt les cartes jouées pour trouver la première couleur jouée	
	for (size_t i = 0; i < getNbJoueurs(); i++)
	{
		const auto& cartes = getPlis()[i]->getListeCartePaquet();
		
	}

	return 0;
}
bool DameDePique::checkPlis() {}

const int DameDePique::playFirst() {
	if (getJoueurById(0)->getMain().PaquetSize() == 13) {
		for (size_t i=0; i<getNbJoueurs(); i++)
		{
			const auto& cartes = getJoueurById(i)->getMain().getListeCartePaquet();

			for (const auto& carte : cartes)
			{
				if (carte->getValeur() == "2" &&
					carte->getCouleur() == "Trefle")
				{
					setIdPremierJoueur(i)
					return i;
				}
			}
		}

	}
	else {
		return gagnantPlis();
	}
}
const int DameDePique::playNext() {
	int idgagnant = gagnantPlis();
	return idgagnant;
}

void DameDePique::compterPoint() {
	for (size_t i = 0; i < getNbJoueurs(); i++)
	{
		const auto& plis = getTeam()[i]->getPlisGagne();
		int pointEquipe = 0;
		for (const auto& pli : plis)
		{
			const auto& cartes = pli->getListeCartePaquet();

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
			for (size_t j = 0; j < getNbEquipe(); j++)
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
