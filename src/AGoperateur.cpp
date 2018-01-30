//============================================================================
// Name        : AlgoGenetic.cpp
// Author      : jianglei wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "math.h"
#include "AGoperateur.h"
#include <typeinfo>
#include <string>
using namespace std;

void AlgoGenetic::initialisation_robot(float pc,float pm,int tp,int n,robot r,int p[][]){
	this->ProbaCrossover=pc;
	this->ProbaMutate=pm;
	this->TaillePop=tp;
	this->N=n;
	int a,b,i,j=1;
		for(i=0;i<tp;i++){
			p[1][i]=r.getEntre();
			a=rand()%99;
			do{
				do{
				p[j][i]=rand()%100;
				}while(r.isObstacles(p[j][i])==true&&p[j][i]<p[j-1][i]);
				j++;
			}while(j<a);
			p[a][i]=r.getSortie();
			for(j=a;j<101;j++){
				p[j][i]=NULL;
			}
		}
	this->pop=p;
}

float AlgoGenetic::fitness_robot(int chemin[]){
	int i=0;
	float fitness,distance=0,f[];
	do{
		distance=sqrt(pow((int)(chemin[i+1]/10)-(int)(chemin[i]/10),2)+pow(chemin[i+1]%10-chemin[i]%10,2))+distance;
		i++;
	}while(chemin[i+1]==NULL|i==99);
	fitness=(1+1/sqrt(i-1))*distance;
	f[0]=distance;
	f[1]=fitness;
	return f;
}

bool AlgoGenetic::suppression(int chemin[],robot r){
	bool b=false;
	int i=0,j=1;
	do{
		do{
			if (chemin[i]==chemin[j]){
				b=true;
			}
			else {
				j++;
			}
		}while(chemin[j]==NULL|b==true);
		i++;
	}while(b==true|chemin[i+1]==NULL);
	return b;
}

int AlgoGenetic::mutation_robot(int chemin[]){
	if (rand()<ProbaMutate){
		chemin[rand()%sizeof(chemin)]=rand()%100;
	}
	return chemin;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
