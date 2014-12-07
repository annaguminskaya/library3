//////////////////////////////////////////MY TEMPLATE////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _ASSOC_H
#define _ASSOC_H
#include <iostream>
#include <map>
#include "Template.h"
#include <string>
#include "LessonType.h"


ostream & operator <<(ostream &, const pair<string, Subject> &);

class Assoc{
private:
	Mymap </*const*/ int, Subject> arr; // контейнер мар содержит связку шифр объекта и указатель на дисциплину
public:
	Assoc(){}
	Assoc(/*const */Assoc &);
	~Assoc();
	Assoc& operator = (/*const*/ Assoc &);
	void insert(const int, const Subject);
	void deletef(const int);
	void change (const int);
	void change_lec (const int);
	void change_sem (const int);
	void change_lab (const int);
	void show();
	friend class AssocIt;
	friend class Subject;
	typedef AssocIt Iterator;
	Iterator begin(); // возвращает итератор, который ссылается на первый элемент в контейнере
	Iterator end(); // возвращает итератор, который ссылается на элемент "следующий за последним"
	Iterator find(const int);
};

class AssocIt{
private:
	Mymap</*const*/ int, Subject>::Iterator cur; // ключ извлекается с помощью (*it).first, значение - (*it).second
public:
	AssocIt(){}
	AssocIt(Mymap</*const*/int, Subject>::Iterator it) :cur(it) {};
	int operator !=(const AssocIt &) const;
	int operator ==(const AssocIt &) const;
	friend class Subject;
	Pair</*const*/ int, Subject> & operator *(); // возвращаем ссылку на объект
	AssocIt & operator ++();
	AssocIt operator ++(const int);
};

#endif



