/*
 * AGoperateur.h
 *
 *  Created on: 2018-1-29
 *      Author: Jianglei, Yuxin
 */

#ifndef AGOPERATEUR_H_
#define AGOPERATEUR_H_

class AGoperateur{
public:
	void initialisation_robot(float,float,int,int,robot);
	float fitness_robot(int);
	chemin insertion(int,robot);
	int selection_robot(float);
	chemin crossover_robot(chemin,chemin,);
	chemin mutation_robot(int a);
	bool suppression(int);
	
	vector<chemin> CreerPopulation();
	vector<chemin> selection();
	chemin croisement_EdT(chemin, chemin);
	void mutation_EdT(chemin);
	int fitness_EdT(chemin);

private:
	float ProbaCrossover;
	float ProbaMutate;
	int TaillePop;
	int N;
	chemin pop[TaillePop];
	float dis[TaillePop];
	float fit[TaillePop];
};



#endif /* AGOPERATEUR_H_ */
