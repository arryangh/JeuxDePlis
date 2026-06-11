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
	pointsGagnant = 25;
	table = new TableJeu();
	ordreCarte = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As" };
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
	cout << "\n=== Cartes distribuées ===" << endl;
	for (int j = 0; j < getNbJoueurs(); j++) {
		cout << getJoueurById(j)->getNom() << " : ";
		for (const auto& c : getJoueurById(j)->getMain().getListeCartePaquet()) {
			cout << c->getValeur() << " de " << c->getCouleur() << "  ";
		}
		cout << endl;
	}
}

bool DameDePique::checkCoeurBrise() {
	return Coeur_Brise;
}

bool DameDePique::checkWin() {
	for (size_t i = 0; i < getNbEquipe(); i++) {
		if (getTeam()[i]->getNbPoint() >= getPointsGagnant()) {
			cout << "\n*** " << getTeam()[i]->getTeamNom() << " a atteint " << getPointsGagnant() << " points — partie terminée ! ***" << endl;
			return true;
		}
	}
	return false;
}

int DameDePique::gagnantPlis() {
	TableJeu& table = getTable();
	PaquetCarte& plis = table.getPlis();
	int idFirstJoueur = table.getIdPremierJoueur();

	// La carte i du plis a été jouée par le joueur (idFirstJoueur + i) % nbJoueurs
	// indexGagnant = index dans le tableau du plis, idgagnant = id du joueur gagnant
	int indexGagnant = 0;
	int idgagnant = idFirstJoueur;
	string firstCouleur = plis.getListeCartePaquet()[0]->getCouleur();

	for (int i = 1; i < getNbJoueurs(); i++)
	{
		const auto& carte = plis.getListeCartePaquet()[i];
		if (carte->getCouleur() == firstCouleur) {
			if (CompareCarte(carte, plis.getListeCartePaquet()[indexGagnant])) {
				indexGagnant = i;
				idgagnant = (idFirstJoueur + i) % getNbJoueurs();
			}
		}
	}
	table.setIdPremierJoueur(idgagnant);
	return idgagnant;
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
		for (int i = 0; i < getNbJoueurs(); i++)
		{
			const auto& cartes = getJoueurById(i)->getMain().getListeCartePaquet();
			for (const auto& carte : cartes)
			{
				if (carte->getValeur() == "2" && carte->getCouleur() == "Trèfle")
				{
					table->setIdPremierJoueur(i);
					cout << "\n" << getJoueurById(i)->getNom() << " commence (possède le 2 de Trèfle)." << endl;
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
	cout << "\n--- Résultat de la manche ---" << endl;
	for (int i = 0; i < getNbJoueurs(); i++)
	{
		const auto& plis = getTeam()[i]->getPlisGagne();
		int pointManche = 0;
		for (const auto& pli : plis)
		{
			const auto& cartes = pli.getListeCartePaquet();
			for (const auto& carte : cartes)
			{
				if (carte->getCouleur() == "Coeur")
				{
					pointManche += 1;
				}
				else if (carte->getCouleur() == "Pique" && carte->getValeur() == "Dame")
				{
					pointManche += 13;
				}
			}
		}
		if (pointManche == 26) {
			cout << getTeam()[i]->getTeamNom() << " a fait le grand chelem ! (+26 pour tous les autres)" << endl;
			pointManche = 0;
			for (int j = 0; j < getNbEquipe(); j++)
			{
				if (j != i) {
					getTeam()[j]->setNbPoint(getTeam()[j]->getNbPoint() + 26);
				}
			}
		}
		getTeam()[i]->setNbPoint(getTeam()[i]->getNbPoint() + pointManche);
		cout << getTeam()[i]->getTeamNom() << " : +" << pointManche << " pts cette manche" << endl;
	}

	cout << "\n--- Scores cumulés ---" << endl;
	for (int i = 0; i < getNbEquipe(); i++) {
		cout << getTeam()[i]->getTeamNom() << " : " << getTeam()[i]->getNbPoint() << " pts" << endl;
	}
}

void DameDePique::jouer() {
	TableJeu* table = &getTable();
	creerPaquetJeu();
	int numeroManche = 1;
	while (!checkWin()) {
		cout << "\n========== MANCHE " << numeroManche << " ==========" << endl;
		paquetJeu.MelangerPaquet();
		distribuer();
		playFirst();
		int numPli = 1;
		while (getJoueurById(0)->getMain().PaquetSize() > 0) {
			int premierJoueur = table->getIdPremierJoueur();
			cout << "\n--- Pli " << numPli << " --- (commence : " << getJoueurById(premierJoueur)->getNom() << ")" << endl;

			for (int i = 0; i < getNbJoueurs(); i++) {
				int idJoueur = (premierJoueur + i) % getNbJoueurs();
				cout << getJoueurById(idJoueur)->getNom() << " joue : ";
				getJoueurById(idJoueur)->jouerCoup();
			}

			if (!Coeur_Brise) {
				for (const auto& carte : table->getPlis().getListeCartePaquet()) {
					if (carte->getCouleur() == "Coeur") {
						Coeur_Brise = true;
						cout << "Les coeurs sont brisés !" << endl;
						break;
					}
				}
			}

			// Afficher le contenu du pli
			cout << "Cartes du pli : ";
			const auto& cartesPli = table->getPlis().getListeCartePaquet();
			for (const auto& c : cartesPli) {
				cout << c->getValeur() << " de " << c->getCouleur() << "  ";
			}
			cout << endl;

			int idgagnantplis = gagnantPlis();
			cout << "--> " << getJoueurById(idgagnantplis)->getNom() << " remporte le pli." << endl;

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
			numPli++;
		}
		compterPoint();
		for (int i = 0; i < getNbEquipe(); i++) {
			getTeam()[i]->clearPlis();
		}
		creerPaquetJeu();
		numeroManche++;
		Coeur_Brise = false;
	}
}

void DameDePique::configurerTeam() {
	vector<Team*> teams;
	for (auto& joueur : joueurs) {
		Team* team = new Team(joueur->getNom());
		team->setJoueurs({ joueur });
		teams.push_back(team);
	}
	setTeam(teams);
}