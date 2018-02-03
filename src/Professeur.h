/*
 * Professeur.h
 *
 *  Created on: 2018-1-28
 *      Author: zoe
 */

#ifndef PROFESSEUR_H_
#define PROFESSEUR_H_

class Professeur {
public:
	Professeur(int,string);
	void setNomP(int);
	string getNomP(int);
	void setCoursE(int);
	list<string> getCoursE(int);

private:
	int IdProf;
	string NomProf;
	map<IdProf,string> Prof;
	map<IdProf,list<int>> CoursE; //a partir d'identifiant du prof pour obtenir liste de cours(les identifiants du cours) que ce prof enseigne
	list<int> CoursEnseigner;
};

#endif /* PROFESSEUR_H_ */
