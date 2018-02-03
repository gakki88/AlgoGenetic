/*
 * Professeur.cpp
 *
 *  Created on: 2018-1-28
 *      Author: zoe
 */
#include "string"
#include "list"
#include "iostream"
#include "sstream"
#include "iterator"
#include "Professeur.h"

using namespace std;

Professeur::Professeur(int id, string nom) {
	this->IdProf=id;
	this->NomProf=nom;
	Prof[IdProf]=NomProf;

}

void Professeur::setNomP(int id, string nom){
	map<int,string>::iterator i=Prof.find(id);
	i->second = nom;

}

string Professeur::getNomP(int id){
	return Prof[id];
}

list<int> Professeur::getCoursE(int id){
	map<int,list<int> >::iterator i = CoursE.find(id);
	return i->second;
}

Professeur::~Professeur() {
	// TODO Auto-generated destructor stub
}
