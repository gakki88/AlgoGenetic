/*
 * cours.h
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */
#include <string>
#ifndef COURS_H_
#define COURS_H_

class cours {
public:
	cours();
	string getNomC(int);

private:
	int idCours;
	string NomCours;
};

#endif /* COURS_H_ */
