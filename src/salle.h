/*
 * salle.h
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */
#include <string>
#ifndef SALLE_H_
#define SALLE_H_

class salle {
public:
	salle();
	int getNbChaise(int);
	bool SiEquipe(int);
	string getNomS(int);

private:
	int idSalle;
	string NomSalle;
	int NbChaises;
	bool Equipement;


};

#endif /* SALLE_H_ */
