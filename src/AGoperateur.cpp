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
#include <vector>
#include "robot.h"
using namespace std;

void AGoperateur::initialisation_robot(float pc,float pm,int tp,robot r){
	this->ProbaCrossover=pc;
	this->ProbaMutate=pm;
	this->TaillePop=tp;
	int a,b,i,j=1;
	this->pop=new chemin[tp];
	srand(time(NULL));
		for(i=0;i<tp;i++){
			j=1;
			pop[i].insert(r.getEntre());
			a=rand()%99;
			if(a!=0){
			do{
				do{
				b=rand()%100+1;
				}while(r.isObstacles(b)==true&&suppression(pop[i],b));
				pop[i].insert(b);
				j++;
			}while(j<=a);
			}
			pop[i].insert(r.getSortie());


		}
}

void AGoperateur::fitness_robot(robot r){
	int i;
	bool bad_line=false;
	float fitness,distance=0, d;
	for(int a=0;a<TaillePop;a++){
		i=0;
	while(i<pop[a].longeur()-1&&bad_line==false){
		if (r.passObstacles(pop[a].showdata(i),pop[a].showdata(i+1))){
					bad_line=true;
				}
		i++;
	}
	i=0;
	if(bad_line==false){
	do{
		distance=sqrt(pow((int)((pop[a].showdata(i+1)-1)/10)-(int)((pop[a].showdata(i)-1)/10),2)+pow((pop[a].showdata(i+1)-1)%10-(pop[a].showdata(i)-1)%10,2))+distance;
		i++;
	}while(i<pop[a].longeur()-1);
	d=distance/100;
	fitness=(1+1/sqrt(i))/d;
	dis[a]=distance;
	fit[a]=fitness;
	}else{
		dis[a]=0;
		fit[a]=pow(10,-6);
	}
	}
}

int AGoperateur::calculFit(chemin c,robot r){
	int i;
		bool bad_line=false;
		float fitness,distance=0, d;
			i=0;
		while(i<c.longeur()-1&&bad_line==false){
			if (r.passObstacles(c.showdata(i),c.showdata(i+1))){
						bad_line=true;
					}
			i++;
		}
		i=0;
		if(bad_line==false){
		do{
			distance=sqrt(pow((int)((c.showdata(i+1)-1)/10)-(int)((c.showdata(i)-1)/10),2)+pow((c.showdata(i+1)-1)%10-(c.showdata(i)-1)%10,2))+distance;
			i++;
		}while(i<c.longeur()-1);
		d=distance/100;
		fitness=(1+1/sqrt(i))/d;
		}else{

			fitness=pow(10,-6);
		}
		return fitness;
}

int AGoperateur::selection_robot(){
	int i,t=0;
	float p,sum=0,b[TaillePop+1];
	b[0]=0;
	for(i=0;i<TaillePop;i++){
		sum=sum+fit[i];
	}
	for(i=0;i<TaillePop;i++){
			b[i+1]=b[i]+fit[i];
	}
	p=sum*rand()/float(RAND_MAX);
	while(p>b[t]){
		t++;
	}
	return t-1;
}

void AGoperateur::crossover_robot(chemin& c1,chemin& c2){
	chemin r1,r2;
		int p1,p2,i,j,k,l;
		vector<int> d1,d2;
		srand(time(NULL));
		if(rand()/float(RAND_MAX)<ProbaCrossover){
		p1=rand()%(c1.longeur()-1)+1;
		p2=rand()%(c2.longeur()-1)+1;
		for(i=0;i<p1;i++){
		r1.insert(c1.showdata(i));
		}
		for(j=p2;j<c2.longeur();j++){
			r1.insert(c2.showdata(j));
		}
		for(k=0;k<p2;k++){
			r2.insert(c2.showdata(k));
		}
		for(l=p1;l<c1.longeur();l++){
			r2.insert(c1.showdata(l));
		}

		}else{
			r1=c1;
			r2=c2;
		}

				c1=r1;
				c2=r2;

}

void AGoperateur::supprimer(chemin& o){
	vector<int> d;
	int i,j;
			d.reserve(100);
			for(i=0;i<o.longeur()-1;i++){
				for(j=i+1;j<o.longeur();j++){
					if(o.showdata(i)==o.showdata(j)){
						d.push_back(j);
					}
				}
			}
			int s=d.size();
			for(i=0;i<s;i++){
						o.erase(d.at(i));
					}


}

bool AGoperateur::suppression(chemin& c,int a){
	bool b=false;
	int i=0;
	do{

			if (c.showdata(i)==a){
				b=true;
			}


		i++;
	}while(b==false&&i<c.longeur());

	return b;
}

void AGoperateur::mutation_robot(chemin& c){
	srand(time(NULL));
	int i=0,p;
	do{
	if (rand()/float(RAND_MAX)<ProbaMutate){
		do{
			p=rand()%100+1;
		}while(suppression(c,p));


		c.setData(i,p);
	}
	i++;
	}while(i<c.longeur());

}

void AGoperateur::evolve(robot r){
	chemin* newPop=new chemin[TaillePop];
	chemin* child=new chemin[TaillePop];
	chemin c1,c2;
	int p;
	fitness_robot(r);
	srand(time(NULL));
	for(int i=0;i<TaillePop;i++){
		int id=selection_robot();
		newPop[i]=pop[id];

	}

	if(TaillePop%2==0){
	for(int i=0;i<TaillePop;i+=2){
		p=rand()%TaillePop;
		c1=newPop[i];
		c2=newPop[p];
		crossover_robot(c1,c2);
		mutation_robot(c1);
		mutation_robot(c2);
		child[i]=c1;
		child[i+1]=c2;

	}
	}else{
		for(int i=0;i<TaillePop-1;i+=2){
				p=rand()%TaillePop;
				c1=newPop[i];
				c2=newPop[p];
				crossover_robot(c1,c2);
				child[i]=c1;
				child[i+1]=c2;
		}
		p=rand()%TaillePop;
		c1=newPop[TaillePop-1];
		c2=newPop[p];
		crossover_robot(c1,c2);
		supprimer(c1);
		supprimer(c2);
		mutation_robot(c1);
		mutation_robot(c2);
		if(calculFit(c1,r)>calculFit(c2,r)){
		child[TaillePop-1]=c1;
		}else{
			child[TaillePop-1]=c2;
		}

	}
	this->pop=child;
}

chemin AGoperateur::getChemin(int a){
	chemin p;
	p=pop[a];
	return p;
}

float AGoperateur::getProbacross(){
	float p;
	p=this->ProbaMutate;
	return p;
}

void AGoperateur::getFit(){
	for(int i=0;i<TaillePop;i++){
		cout<<fit[i]<<endl;
	}
}

int main() {
	robot r;
	r.init_robot(5,86);
	float pc=0.7;
	float pm=0.001;
	int tp=20;
	int N=100;
	int i=0;
	AGoperateur ag;
	ag.initialisation_robot(pc,pm,tp,r);
	while(i<N){
		ag.evolve(r);
		i++;

	}
		float j=0,t;
		for(i=0;i<tp;i++){
			if(j<ag.calculFit(ag.getChemin(i),r)){
				j=ag.calculFit(ag.getChemin(i),r);
				t=i;
			}
		}
		int a=0;
		cout<<"{";
		do{
			cout<<ag.getChemin(t).showdata(a)<<",";
			a++;
		}while(a<ag.getChemin(t).longeur()-1);

		cout<<ag.getChemin(t).showdata(a)<<"}"<<endl;

	return 0;
}
