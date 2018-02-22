/*
 * gene.cpp
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
 *      Author: virgiliaL
 */

#include <iostream>
#include "math.h"
#include "robot.h"
using namespace std;

void robot::init_robot(int e,int s){
	this->entre=e;
	this->sortie=s;
}

bool robot::isObstacles(int chemin){
	bool b=false;
	int i=0;
	int s=sizeof(obstacles)/sizeof(obstacles[0]);
	do{
		if (obstacles[i]==chemin){
			b=true;
		}
		else{
			i++;
		}
	}while(b==false&&i<s);
	return b;
}

bool robot::estVoisin(int a,int b){
	if(a==b+10||a==b-10||a==b+1||a==b-1){
		return true;
	}
	else{
		return false;
	}

}

int robot::max(int a,int b){
	if (a<b){
		return b;
	}
	else{
		return a;
	}
}

int robot::min(int a,int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}

bool robot::passObstacles(int p1,int p2){
	bool bo=false;
	int i=0;
	int s=sizeof(obstacles)/sizeof(obstacles[0]);
	int ox1,ox2,ox3,ox4,oy1,oy2,oy3,oy4;
	float x1,x2,y1,y2,a,b;
	x1=p1%10+0.5;
	x2=p2%10+0.5;
	y1=(int)p1/10+0.5;
	y2=(int)p2/10+0.5;
	a=(y1-y2)/(x1-x2);
	b=y1-a*x1;
	do{
		if((int)obstacles[i]/10+0.5<=max(y1,y2)&&
				(int)obstacles[i]/10+0.5>=min(y1,y2)&&
				obstacles[i]%10+0.5<=max(x1,x2)&&
				obstacles[i]%10+0.5>=min(x1,x2)&&!estVoisin(obstacles[i],a)&&!estVoisin(obstacles[i],b)){

			ox1=(int)obstacles[i]/10;
			ox2=ox1;
			ox3=ox1+1;
			ox4=ox3;
			oy1=obstacles[i]%10;
			oy2=oy1+1;
			oy3=oy1;
			oy4=oy2;
			if((a*ox1+b-oy1)*(a*ox2+b-oy2)<0||(a*ox1+b-oy1)*(a*ox3+b-oy3)<0||(a*ox1+b-oy1)*(a*ox4+b-oy4)<0||(a*ox2+b-oy2)*(a*ox3+b-oy3)<0
					||(a*ox2+b-oy2)*(a*ox4+b-oy4)<0||(a*ox3+b-oy3)*(a*ox4+b-oy4)<0){
				bo=true;
			}
		}
		i++;

	}while(bo==false&&i<s);
		return bo;

}

int robot::getEntre(){
	return entre;
}

int robot::getSortie(){
	return sortie;
}

