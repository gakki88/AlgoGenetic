/*
 * gene.cpp
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
 *      Author: virgiliaL
 */

#include <iostream>
#include "math.h"
#include "gene.h"
using namespace std;

void robot::init_robot(int e,int s,int o[]){
	this->entre=e;
	this->sortie=s;
	this->obstacles=o;
}

bool robot::isObstacles(int chemin){
	bool b=false;
	int i=0;
	do{
		if (obstacles[i]==chemin){
			b=true;
		}
		else{
			i++;
		}
	}while(b==true|i==sizeof(obstacles)+1);
	return b;
}

int robot::getEntre(){
	return entre;
}

int robot::getSortie(){
	return sortie;
}
