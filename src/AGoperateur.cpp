//============================================================================
// Name        : AlgoGenetic.cpp
// Author      : jianglei, yuxin
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

void AGoperateur::initialisation_robot(float pc,float pm,int tp,int n,robot r,int p[][]){
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

float AGoperateur::fitness_robot(int chemin[]){
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

bool AGoperateur::suppression(int chemin[],robot r){
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

int AGoperateur::mutation_robot(int chemin[]){
	if (rand()<ProbaMutate){
		chemin[rand()%sizeof(chemin)]=rand()%100;
	}
	return chemin;
}

vector<chemin> AGoperateur::CreerPopulation(){
	vector<chemin> pop;
	vector<int> myVec;
	chemin c;

	for(int n=0;n<100;n++){

		for (int i=1; i<28; ++i) myVec.push_back(i);
		random_shuffle ( myVec.begin(), myVec.end());
		for (std::vector<int>::iterator it=myVec.begin(); it!=myVec.end(); ++it)
		    	c.insert((int) *it);

		pop.push_back(c);
		c.clear();

	}

	return pop;
}

vector<chemin> AGoperateur::selection(vector<chemin> pop){
	vector<chemin> selected;
	int randIndex;

	for (int i=0;i<9;i++){

		randIndex = rand()%100;
		selected.push_back(pop[randIndex]);

	}

	return selected;

}

chemin AGoperateur::croisement_EdT(chemin c1,chemin c2){
	chemin cEnfant;
	int randIndex;

	randIndex = rand()%27;


	for(int i=0;i<randIndex;i++){
		cEnfant.insert(c1.showdata(i));
		for(int j=0;j<27;j++){
			if(c2.showdata(j)==c1.showdata(i)){
				c2.erase(j);
			}
		}
	}

	concat(cEnfant,c2);

	return cEnfant;
}

void AGoperateur::mutation_EdT(chemin c){
	int r1,r2;

	r1=rang()%27;
	r2=rand()%27;

	c.insert_pos(c.showdata(r2),r1);
	c.insert_pos(c.showdata(r1+1),r2+1);
	c.erase(r1+1);
	c.erase(r2+1);
}


/*int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}*/
