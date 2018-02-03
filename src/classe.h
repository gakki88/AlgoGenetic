/*
 * classe.h
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */

#ifndef CLASSE_H_
#define CLASSE_H_

class classe {
public:
	classe();
	int getCours(int);
	int getProf(int);
	int getNbEtud(int);
	bool getEquiR(int);
	float getDure(int);
	int getNote(int);


private:
	int RefCours;
	int RefProf;
	list<int> RefGroupe;
	int NbEtudiant;
	bool EquipeRequis;
	float duree;
	int note;
};

#endif /* CLASSE_H_ */
