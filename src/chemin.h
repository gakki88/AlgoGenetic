/*
 * chemin.h
 *
 *  Created on: 2018Äê2ÔÂ4ÈÕ
 *      Author: virgiliaL
 */

#ifndef CHEMIN_H_
#define CHEMIN_H_
#include <iostream>

class chemin{
public:
	chemin(){create_Chemin();}
	~chemin(){clear();}
	void create_Chemin();
	void insert(const int&);//一个一个插入结点
	void insert_pos(int,const int&);//在第n号位置后面插入一个数值为d的结点
	void erase(int);//删除第n个位置上的结点
	int showdata(int);//查看第n号位置上的数
	void setData(int,int);//修改第n号位置上的数
private:
	struct Point{
		int data;
		Point * next;
		Point(const int& d):data(d),next(NULL){}
	};
	Point * head,*tail;
	void clear();
	Point * find(int pos){
		Point * p = head;
		int position=0;
				while(p!=NULL&&position!=pos){
					position++;
					p=p->next;
				}
		return p;
	};


};

