/*
 * AGoperateur.h
 *
 *  Created on: 2018-1-29
 *      Author: Jianglei, Yuxin
 */

#ifndef AGOPERATEUR_H_
#define AGOPERATEUR_H_

#include"chemin.h"
#include "robot.h"

class AGoperateur{
public:

	void initialisation_robot(float,float,int,robot);
	float getProbacross();
	void fitness_robot(robot);
	void supprimer(chemin&);
	int calculFit(chemin,robot);
	//chemin insertion(int,robot);
	int selection_robot();
	void crossover_robot(chemin&,chemin&);
	void mutation_robot(chemin&);
	bool suppression(chemin&,int);
	void evolve(robot);
	chemin getChemin(int);
	void getFit();
	~AGoperateur(){
		//delete [] pop;
	}


private:
	float ProbaCrossover;
	float ProbaMutate;
	int TaillePop;
	chemin* pop;
	float dis[200];
	float fit[200];
};



#endif /* AGOPERATEUR_H_ */
#endif /* AGOPERATEUR_H_ */
