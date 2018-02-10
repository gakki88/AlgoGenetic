/*
 * gene.h
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
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
	bool passObstacles(int,int);
	bool estVoisin(int,int);
	int getEntre();
	int getSortie();
	int max(int,int);
	int min(int,int);

private:
	int entre;
	int sortie;
	int obstacles[];
};

class classe:public gene{

};

#endif /* GENE_H_ */
