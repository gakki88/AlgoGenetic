/*
 * gene.h
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
 *      Author: virgiliaL
 */

#ifndef ROBOT_H_
#define ROBOT_H_

class robot{
public:
	/*robot(){
		entre = 1;
		sortie=100;
		vector<int> obstacles(23,0);
	}*/
	void init_robot(int,int);
	void plot(int*);
	bool isObstacles(int);
	bool passObstacles(int,int);
	bool estVoisin(int,int);
	int getEntre();
	int getSortie();
	int max(int,int);
	int min(int,int);
	//~robot() {delete [] obstacles;}

private:
	int entre;
	int sortie;
	//const int obstacles[23]={4,9,10,11,14,17,20,27,30,33,34,44,49,57,62,65,77,78,82,87,88,92,96};
	const int obstacles[23]={4,96};
};



#endif /* ROBOT_H_ */
