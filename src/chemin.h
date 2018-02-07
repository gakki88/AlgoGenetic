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
	void insert(const int&);
	void insert_pos(int,const int&);
	void erase(const int&);
	void updata(const int&,const int&);
	int showdata(int);
	void setData(int,int);
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
		return p->next;
	};


};



#endif /* CHEMIN_H_ */
