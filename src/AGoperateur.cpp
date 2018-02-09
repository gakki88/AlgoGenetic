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
#include <ctime>
using namespace std;

void AGoperateur::initialisation_robot(float pc,float pm,int tp,int n,robot r){
	this->ProbaCrossover=pc;
	this->ProbaMutate=pm;
	this->TaillePop=tp;
	this->N=n;
	int a,b,i,j=1;
	chemin p[tp];
	srand(time(0));
		for(i=0;i<tp;i++){
			p[i].insert(r.getEntre());
			a=rand()%99;
			if(a!=0){
			do{
				do{
				b=rand()%100+1;
				}while(r.isObstacles(b)==true);
				p[i].insert(b);
				j++;
			}while(j<=a);
			}
			p[i].insert(r.getSortie());

		}
	this->pop=p;
}

float AGoperateur::fitness_robot(int a){
	int i=0;
	float fitness,distance=0,f[2];
	do{
		distance=sqrt(pow((int)(pop[a].showdata(i+1)-1/10)-(int)(pop[a].showdata(i)-1/10),2)+pow(pop[a].showdata(i+1)-1%10-pop[a].showdata(i)-1%10,2))+distance;
		i++;
	}while(pop[a].showdata(i+1)!=0|i!=99);
	fitness=(1+1/sqrt(i))/distance;
	f[0]=dis[a]=distance;
	f[1]=fit[a]=fitness;

	return f;
}

int AGoperateur::selection_robot(float f){
	int i,b[TaillePop+1],p,t=0;
	float sum=0;
	b[0]=0;
	for(i=0;i<TaillePop;i++){
		sum=sum+fit[i];
	}
	for(i=0;i<TaillePop;i++){
		b[i+1]=b[i]+fit[i]/sum;
	}
	srand(time(NULL));
	p=rand()/float(RAND_MAX);
	while(p>b[t]){
		t++;
	}
	return t-1;
}


bool AGoperateur::suppression(int a){
	bool b=false;
	int i=0,j=1;
	do{
		do{
			if (pop[a].showdata(i)==pop[a].showdata(j)){
				b=true;
			}
			else {
				j++;
			}
		}while(pop[a].showdata!=0|b==true);
		i++;
	}while(b==true|pop[a].showdata(i+1)!=0);

	return b;
}

chemin AGoperateur::mutation_robot(int a){
	srand(time(0));
	int i=0,p;
	do{
	if (rand()/float(RAND_MAX)<ProbaMutate){
		do{
			p=rand()%100+1;
			pop[a].setData(i,p);
		}while(suppression(i));
	}
	i++;
	}while(pop[a].showdata(i)!=0);
	return pop;
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
