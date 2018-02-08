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
	void initialisation_robot(float,float,int,int,robot,int[][]);
	float fitness_robot(int*);
	int insertion(int*);
	void selection_robot(float);
	int crossover_robot(int*,int*);
	int mutation_robot(int*);
	bool suppression(int*,robot);
	
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
	int pop[][];
};



#endif /* AGOPERATEUR_H_ */
