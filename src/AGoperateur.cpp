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
#include "gene.h"
using namespace std;

void AGoperateur::initialisation_robot(float pc,float pm,int tp,int n,robot r){
	this->ProbaCrossover=pc;
	this->ProbaMutate=pm;
	this->TaillePop=tp;
	this->N=n;
	try{
		while(true){
	this->pop=new chemin[tp];
	this->fit=new float[tp];
	this->dis=new float[tp];
		}
	}catch(const std::bad_alloc& e){
		std::cout << "Allocation failed: " << e.what() << '\n';
	}
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
				}while(r.isObstacles(b)==true||suppression(p[i],b));
				p[i].insert(b);
				j++;
			}while(j<=a);
			}
			p[i].insert(r.getSortie());

		}
	this->pop=p;
}

float* AGoperateur::fitness_robot(int a,robot r){
	int i=0;
	bool bad_line=false;
	float fitness,distance=0;
	float* f=new float[2];
	while(i!=99||bad_line==false){
		if (r.passObstacles(pop[a].showdata(i),pop[a].showdata(i+1))){
					bad_line=true;
				}
		i++;
	}
	i=0;
	if(bad_line==false){
	do{
		distance=sqrt(pow((int)(pop[a].showdata(i+1)-1/10)-(int)(pop[a].showdata(i)-1/10),2)+pow(pop[a].showdata(i+1)-1%10-pop[a].showdata(i)-1%10,2))+distance;
		i++;
	}while(pop[a].showdata(i+1)!=0||i!=99||bad_line==false);

	fitness=(1+1/sqrt(i))/distance;
	f[0]=dis[a]=distance;
	f[1]=fit[a]=fitness;
	}else{
		f[0]=dis[a]=0;
		f[1]=fit[a]=pow(10,-6);
	}
	return f;
}

int AGoperateur::selection_robot(){
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

chemin* AGoperateur::crossover_robot(chemin c1,chemin c2){
	chemin* child=new chemin[2];
	int p1,p2;
	srand(time(NULL));
	if(rand()/float(RAND_MAX)<ProbaCrossover){
	p1=rand()%c1.longeur();
	p2=rand()%c2.longeur();
	for(int i=0;i<p1;i++){
	child[0].insert(c1.showdata(i));
	}
	for(int i=p2;i<c2.longeur();i++){
		child[0].insert(c2.showdata(i));
	}
	for(int i=0;i<p2;i++){
		child[1].insert(c2.showdata(i));
	}
	for(int i=p1;i<c1.longeur();i++){
		child[1].insert(c1.showdata(i));
	}
	}else{
		child[0]=c1;
		child[1]=c2;
	}

	return child;
}

/*chemin AGoperateur::insertion(int a,robot r){
	int i=0;
	do{
		if(r.passObstacles(pop[a].showdata(i),pop[a].showdata(i+1))){


		}
	}while(pop[a].showdata(i+1)!=0);

	return pop;
}*/

bool AGoperateur::suppression(chemin c,int a){
	bool b=false;
	int i=0;
	do{

			if (c.showdata(i)==a){
				b=true;
			}


		i++;
	}while(b==false||c.showdata(i+1)!=0);

	return b;
}

chemin AGoperateur::mutation_robot(chemin c){
	srand(time(0));
	int i=0,p;
	do{
	if (rand()/float(RAND_MAX)<ProbaMutate){
		do{
			p=rand()%100+1;

		}while(suppression(c,p));
		c.setData(i,p);
	}
	i++;
	}while(c.showdata(i)!=0);
	return c;
}

void AGoperateur::evolve(){
	chemin newPop[TaillePop],child[TaillePop];
	chemin c1,c2;
	int p;
	srand(time(0));
	for(int i=0;i<TaillePop;i++){
		newPop[i]=pop[selection_robot()];
	}
	for(int i=0;i<TaillePop;i+=2){
		p=rand()%TaillePop;
		child[i]=crossover_robot(newPop[i],newPop[p])[0];
		child[i+1]=crossover_robot(newPop[i],newPop[p])[1];
		child[i]=mutation_robot(child[i]);
		child[i+1]=mutation_robot(child[i+1]);
	}
	this->pop=child;
}

chemin AGoperateur::getChemin(int a){
	return pop[a];
}

int main() {
	robot r;
	int o[23]={4,9,10,11,14,17,20,27,30,33,34,44,49,57,62,65,77,78,82,87,88,92,96};
	r.init_robot(1,100,o);
	float pc=0.7;
	float pm=0.001;
	int tp=20;
	int N=50;
	int i=0;
	AGoperateur ag;
	ag.initialisation_robot(pc,pm,tp,N,r);
	while(i<50){
		ag.evolve();
	}
	float j=0,t;
	for(i=0;i<tp;i++){
		if(j<ag.fitness_robot(i,r)[1]){
			j=ag.fitness_robot(i,r)[1];
			t=i;
		}
	}
	int a=0;
	cout<<"{";
	do{
		cout<<ag.getChemin(t).showdata(a)<<",";
		a++;
	}while(ag.getChemin(t).showdata(i)!=0);
	return 0;
}
