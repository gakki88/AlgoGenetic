/*
 * groupe.h
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */

#ifndef GROUPE_H_
#define GROUPE_H_

class groupe {
public:
	groupe();
	string getNomG(int);
	int getNbEtud(int);
	list<int> getCoursA(int);

private:
	int idGroupe;
	string NomG;
	int NbEtudiant;
	list<int> CoursAller;
};

#endif /* GROUPE_H_ */
