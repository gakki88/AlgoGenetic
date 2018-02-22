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

void AGoperateur_EdT::SetParam(float pc,float pm,int n){
	this->ProbaCrossover=pc;
	this->ProbaMutate=pm;
	//this->TaillePop=tp;
	this->N=n;
}

int AGoperateur_EdT::selection(){
	int i,t=0;
	float sum=0,p(0);
	float b[100];
	b[0]=0;
	for(i=0;i<100;i++){
		sum=sum+fit.at(i);
	}
	//cout<<"sum = "<<sum<<"\n b : ";
	for(i=0;i<100;i++){
		b[i+1]=b[i]+fit.at(i)/sum;
		//cout<<b[i+1]<<" ";
	}
	//srand(time(0));
	p=rand()%100;
	p=p/100;
	//cout<<"\n p = "<<p<<endl;
	while(p>b[t]){
		t++;
	}
	//delete[] b;
	return t-1;
}


void AGoperateur_EdT::initialisation_EdT(EdT e){

	int a,b,i,j=1;
	vector<vector<int>> p;
	vector<int> UnGene;
	std::vector<int> arrayNumero;

	p.clear();
	p.reserve(100);

	srand(time(0));

	for(i=0;i<100;i++){
		UnGene.clear();
		UnGene.reserve(28);
		arrayNumero.clear();
		arrayNumero.reserve(70);

		cout<<"entrer dans 1er loop "<<i<<" fois"<<endl;
		b = 70;
		//initiale un tableau de numero a choisir
		for (int i=1; i<71; i++) {arrayNumero.push_back(i);}
		/*cout<<"finir le 2eme loop"<<endl;
		cout<<"arrayNum = ";
		for (vector<int>::iterator it=arrayNumero.begin();it!=arrayNumero.end();it++){
			cout<<(*it)<<" ";
		}
		cout<<endl;*/
		//creer un gene
		for(j=0;j<28;j++){
			//cout<<"entrer dans 3eme loop "<<j<<" fois"<<endl;
			//a = rand()%b; //random un index de 0 a b
			//UnGene.insert((int) arrayNumero.at(a)); //inserer dans le gene le numero indice a
			if(e.getClasse().at(j).getDure()==2){ //verifier si c'est une case pour un cours duree 2 heures
				do{a = rand()%b;//random un index de 0 a b
				}while(e.isObstacles((int)arrayNumero.at(a)));

//cout<<"le a = "<<a<<" et numero = "<<arrayNumero.at(a)<<" et b ="<<b;
				UnGene.push_back((int) arrayNumero.at(a));//inserer dans le gene le numero indice a
				if(a==arrayNumero.size()-1){
					arrayNumero.erase(arrayNumero.begin()+a);
					b--;
				}else{
					if(arrayNumero.at(a+1) ==arrayNumero.at(a)+1){
						arrayNumero.erase(arrayNumero.begin()+a); //si oui, on supprime deux numeros successives dans le tableau arrayNum
						arrayNumero.erase(arrayNumero.begin()+a);
						b=b-2;}
					else{
						arrayNumero.erase(arrayNumero.begin()+a);
						b--;
					}
				}

			}
			//if(e.getClasse().at(j).getDure()==1){//si c'est une case de gene pour un cours duree 1 heure
			else
				{a = rand()%b;//random un index de 0 a b
				//cout<<"le a = "<<a<<" et numero = "<<arrayNumero.at(a)<<"et b ="<<b;
				UnGene.push_back((int) arrayNumero.at(a));//inserer dans le gene le numero indice a
				arrayNumero.erase(arrayNumero.begin()+a); //on supprime juste un numero dans le tableau arrayNum
				b=b-1;
			}
			/*cout<<"arrayNum = ";
			for (vector<int>::iterator it=arrayNumero.begin();it!=arrayNumero.end();it++){
				cout<<(*it)<<" ";
			}
			cout<<endl;*/

		}

		p.push_back(UnGene);
		cout<<"un gene : ";
		for (vector<int>::iterator it=UnGene.begin();it!=UnGene.end();it++){
						cout<<(*it)<<" ";
					}
					cout<<endl;
		cout<<"avoir un gene "<<i<<endl;
	}
	cout<<"sortir de 1er loop"<<endl;

	/*for(int n=0;n<100;n++){

		for (int i=1; i<28; ++i) myVec.push_back(i);
		random_shuffle ( myVec.begin(), myVec.end());
		for (std::vector<int>::iterator it=myVec.begin(); it!=myVec.end(); ++it)
		    	c.insert((int) *it);

		p.push_back(c);
		c.clear();

	}*/

	this->pop = p;
}


vector<vector<int>> AGoperateur_EdT::croisement_EdT(EdT e,vector<int> c1,vector<int> c2){
	vector<int> temp1,temp2;
	vector<vector<int>> Enfant;
	int randIndex;

	Enfant.reserve(2);
	if((int)rand()%100 > ProbaCrossover*100){
		Enfant.push_back(c1);
		Enfant.push_back(c2);
	}else{
//obtenir un point de coupture aleatoire
		randIndex = rand()%28;

		temp1 = c1;
		temp2 = c2;

		swap_ranges(temp1.begin()+randIndex, temp1.end(), temp2.begin()+randIndex);

		Enfant.push_back(temp1);
		Enfant.push_back(temp2);
	}
	return Enfant;
}

void AGoperateur_EdT::mutation_EdT(vector<int> c){
	int r1,r2;

	if(rand()%100<ProbaMutate*100){

	r1=rand()%28;
	r2=rand()%28;

	swap_ranges(c.begin()+r1, c.begin()+r1, c.begin()+r2);
	}
}

void AGoperateur_EdT::evolve(EdT e){
	vector<vector<int>> newPop,child;
	vector<int> c1,c2;
	int p;

	newPop.clear();
	child.clear();
	newPop.reserve(100);
	child.reserve(100);
	//srand(time(0));
	for(int i=0;i<100;i++){
		int r=selection();
		newPop.push_back(pop.at(r));
		cout<<i<<" r = "<<r<<" ";

	}
	cout<<"sortir 1er for"<<endl;
	for(int i=0;i<100;i+=2){
		p=rand()%100;
		child.push_back(croisement_EdT(e,newPop[i],newPop[p]).at(0));
		mutation_EdT(child.at(i));
		child.push_back(croisement_EdT(e,newPop[i],newPop[p]).at(1));
		mutation_EdT(child.at(i+1));
	}
	cout<<"sortir 2eme for"<<endl;
	this->pop = child;
	fitness(e);
}


/*float AGoperateur_EdT::fitness_EdT(EdT e,vector<int> c){

		e.calculScore(c);
	return e.getScore();
}*/
void AGoperateur_EdT::fitness(EdT e){
	int i(0);
	vector<int> gene;
	fit.clear();
	fit.reserve(100);
	for(i=0;i<pop.size();i++){
		gene=pop.at(i);
		/*cout<<i<<" ieme gene= ";
		for (vector<int>::iterator it=gene.begin();it!=gene.end();++it){
					cout<<(*it)<<" ";
				}
		cout<<endl;*/
		e.calculScore(gene);
		this->fit.push_back(e.getScore());
		//cout<<fit.at(i)<<endl;

	}

}
