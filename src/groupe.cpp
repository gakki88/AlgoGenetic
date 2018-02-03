/*
 * groupe.cpp
 *
 *  Created on: 2018-2-2
 *      Author: zoe
 */

#include "groupe.h"

groupe::groupe() {
	// TODO Auto-generated constructor stub

}

string groupe::getNomG(int){
	return this->NomG;
}

int groupe::getNbEtud(int){
	return this->NbEtudiant;
}

list<int> groupe::getCoursA(int){
	return this->CoursAller;
}
