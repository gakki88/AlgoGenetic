/*
 * salle.cpp
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */

#include "salle.h"

salle::salle() {
	// TODO Auto-generated constructor stub

}

int salle::getNbChaise(int) {
	return this->NbChaises;
}

bool salle::SiEquipe(int){
	return this->Equipement;
}

string salle::getNomS(int){
	return this->NomSalle;
}
