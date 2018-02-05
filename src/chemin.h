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
	void insert_pos(const int&,const int&);
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
	Point * find(const int& d){
		Point * p = head;
		for(;p;p=p->next){
			if(p->next->data==d)
				break;
		}
		return p->next;
	};


};



#endif /* CHEMIN_H_ */
