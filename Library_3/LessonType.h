#pragma once
#ifndef _LESSONTYPE_H_
#define _LESSONTYPE_H_
#include <iostream>
#include <string>

using namespace std;

struct Laboratories
{
	int index, capacity;
	Laboratories ():index(1), capacity(15) {};
	Laboratories (int i, int c): index(i), capacity(c) {};
};

class LessonType
{
protected:
	int quantity;
	virtual ostream& show(ostream& os)const ;
	virtual istream& get(istream& is);
public:
	LessonType() : quantity(0) {};
	friend class Subject;
	virtual LessonType* clone()const = 0;
	friend ostream& operator <<(ostream &os, /*const*/ LessonType &p)
	{
		return p.show(os);
	}

	friend istream& operator >>(istream &is, LessonType &p)
    {
	 return p.get(is);
    }

	int getquan () const;
	void setquan (int n);
	virtual int type() const = 0;
	virtual ~LessonType(){}
};

class Lection: public LessonType
{
private:
	string index[10];
	string annot;
	int control;  

public:
	Lection () ;
	virtual ostream& show(ostream& os)const;
	virtual istream& get(istream& is);
	virtual int type () const;
	virtual Lection* clone() const;
};

class Seminar: public LessonType
{
private:
	int control;
	int date;
protected:
	virtual ostream& show(ostream& os)const;
	virtual istream& get(istream& is);

public:
	Seminar () ;
	virtual int type () const { return 2;}
	virtual Seminar* clone() const;
	virtual int getdate () const;
	virtual int setdate (int n);
}
;

class Laboratory: public LessonType
{
private:
	
	int duration;
	int date;
	int quan_lab;
	Laboratories lab[3];
protected:
	virtual ostream& show(ostream&)const;
	virtual istream& get(istream&) ;
public:
	Laboratory ();
	virtual int type ()const {return 3;}
	virtual Laboratory* clone() const;
	virtual int getdate () const;
	virtual int setdate (int n);
	int setduration(int n);
	int getduration () const;
	int setquanlab(int n);
	int getquanlab() const;
	int setIndex (int, int);
	int getIndex (int) const;
	int setCapacity (int n, int cap);
	int getCapacity(int) const;
};

class Subject
{
public:
	 string name; 
	 LessonType* ptr[3];
	 int kol;
public:
	 Subject(const string &, LessonType* const [], int);
	 Subject ();
	 ~Subject () ;
	 friend class Assoc;
	 friend class AssocIt;
	 int setSub (const string &, int);
};
#endif