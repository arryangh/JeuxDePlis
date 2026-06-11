#ifndef PAQUET_CARTE_H
#define PAQUET_CARTE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Carte.h"

using namespace std;

class PaquetCarte
{
private:
	vector<unique_ptr<Carte>> listeCartePaquet;

public:
	
	PaquetCarte();

	PaquetCarte(const PaquetCarte&) = delete;
	PaquetCarte& operator=(const PaquetCarte&) = delete;
	
	PaquetCarte(PaquetCarte&&) = default;
	PaquetCarte& operator=(PaquetCarte&&) = default;

	void afficherPaquet();

	void addCarte(std::unique_ptr<Carte> carte);

	void giveCard(size_t indexCarte, PaquetCarte& destination);

	void deleteCard();

	const std::vector<std::unique_ptr<Carte>>& getListeCartePaquet() const;

	void MelangerPaquet();

	size_t PaquetSize() const;
};
#endif