/*
 * gene.h
 *
 *  Created on: 2018��1��29��
 *      Author: virgiliaL
 */

#ifndef GENE_H_
#define GENE_H_

class gene{

};

class robot:public gene{
public:
	void init_robot(int,int,int*);
	void plot(int*);
	bool isObstacles(int);
	int getEntre();
	int getSortie();

private:
	int entre;
	int sortie;
	int obstacles[];
};

class classe:public gene{

};

#endif /* GENE_H_ */
