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
	head = tail =NULL;
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

void chemin::erase(int pos){
	Point * p ;
		Point * q ;
		int i=pos-1;
		if (pos==0){
			q=head;
			head=head->next;
			delete q;
		}else{
		p=find(i);
		q=p->next;
		p->next = p->next->next;
		delete q;
		}
}

int chemin::showdata(int pos){
	Point *p =head;
	if(p==NULL){
		return 0;
	}else{
		p=find(pos);
		}

	return p->data;
}

void chemin::setData(int pos,int d){
	Point *p = head;
	if(p!=NULL){
		p=find(pos);
		if(p!=NULL){
			p->data=d;
		}
	}
}


