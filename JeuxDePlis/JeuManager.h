#include "Jeu.h"

class JeuManager {
private :
	static Jeu* jeuCourant;
public :
	static void setJeuCourant(Jeu* jeu) { jeuCourant = jeu; }

	static Jeu* getJeuCourant() { return jeuCourant; }
};