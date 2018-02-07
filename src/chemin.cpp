/*
 * chemin.cpp
 *
 *  Created on: 2018Äê2ÔÂ4ÈÕ
 *      Author: virgiliaL
 */

#include <iostream>
#include "chemin.h"
using namespace std;

void chemin::clear(){
	Point *p = head;
	while(p){
		Point * q = p->next;
		delete p;
		p=q;
	}
}


void chemin::create_Chemin(){
	head = new Point(0);
}

void chemin::insert(const int& d){
	if(head==NULL){
		head=tail=new Point(d);
		head->next=NULL;
		tail->next=NULL;
	}else{
	Point * p = new Point(d);
	tail->next=p;
	tail=p;
	tail->next=NULL;
	}

}

void chemin::insert_pos(int pos,const int& d1){
	Point * p =find(pos);
	Point * q =new Point(d1);
	q->next = p->next;
	p->next = q;
}

void chemin::erase(const int& d){
	Point * p ;
	Point * q ;
	p=find(d);
	q=p->next;
	p->next = p->next->next;
	delete q;

}

void chemin::updata(const int& d,const int& d1){
	Point * p=find(d);
	p->next->data=d1;
}

int chemin::showdata(int pos){
	Point *p =head;
	if(p==NULL){
		return NULL;
	}else{
		int position=0;
		while(p!=NULL&&position!=pos){
			position++;
			p=p->next;
		}
	}
	return p->data;
}

void chemin::setData(int pos,int d){
	Point *p = head;
	if(p!=NULL){
		int position=0;
		while(p!=NULL&&position!=position){
			position++;
			p=p->next;
		}
		if(p!=NULL){
			p->data=d;
		}
	}
}

