/*
 * AlgoGenetic.h
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
 *      Author: virgiliaL
 */

#ifndef ALGOGENETIC_H_
#define ALGOGENETIC_H_

class AlgoGenetic{
public:
	void initialisation_robot(float,float,int,int,robot,int[][]);
	float fitness_robot(int*);
	int insertion(int*);
	void selection_robot(float);
	int crossover_robot(int*,int*);
	int mutation_robot(int*);
	bool suppression(int*,robot);

private:
	float ProbaCrossover;
	float ProbaMutate;
	int TaillePop;
	int N;
	int pop[][];
};



#endif /* ALGOGENETIC_H_ */
