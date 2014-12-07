#include "StdAfx.h"
#include "LessonType.h"
#include "Template.h"
#include <iostream>
using namespace std;
#define EXAM 1
#define OFFSET 2

 ostream& LessonType::show(ostream& os)const 
	{
		return os << "Quantity: " <<quantity<<endl;
	}

 

 istream& LessonType::get(istream& is)
	{ 
	  return is >> quantity;
    };

 int LessonType::getquan () const
	{
	return quantity;
    }

 void LessonType::setquan (int n)
	{
		if (n>100) throw exception ("Too many hours");
	  quantity = n;
    }

 Lection::Lection () 
	{
		index[0] = "1";
		annot = "Good course ;)";
		control = 1;
		quantity = 1;
	}

 ostream& Lection::show(ostream& os)const
	{
		LessonType::show(os);
		os<<"				Groups: ";
		int i=0;
		while (index[i]!="\0")
	    	{
		      os<<index[i]<<" ";
		      i++;
		    }
		cout<<endl;
		os<<"				Control: ";
		if (control == EXAM) os<<"exam"<<endl;
		if (control == OFFSET) os<<"offset"<<endl;
		if ((control!=EXAM)&&(control!=OFFSET)) os<<"uknown"<<endl;
		return os<< "				Annotation: "<<annot<<endl;
	}
	
 istream& Lection::get(istream& is)
	{
		int n;
		cout<<"Put how many groups:"<<endl;
		is>>n;
		cout<<"Groups:"<<endl;
		for (int i = 0;i<10;i++)
			index[i]="\0";
		for (int i=0;i<n;i++)
			is>>index[i];
		is.ignore();
		cout<<"Annotation"<<endl;
		getline(is, annot);
		cout<<"Quantity:"<<endl;
		LessonType::get(is);
		cout<<"Control (1 - exam, 2 - offset)"<<endl;
		is>>control;
		return is;
	}

 int Lection::type () const
	 {
		return 1;
	 }

Lection* Lection::clone() const
	 {
		return new Lection(*this);
	 }

ostream& Seminar::show(ostream& os)const
  {
		LessonType::show(os);
		os<<"				Control: ";
		if (control == EXAM) os<<"exam"<<endl;
		if (control == OFFSET) os<<"offset"<<endl;
		if ((control!=EXAM)&&(control!=OFFSET)) os<<"uknown"<<endl;
		return os <<"				Date: " << date<<endl ;
	};

istream& Seminar::get(istream& is)
	{
		cout<<"Quantity: --> "<<endl;
		LessonType::get(is);
		cout<<"Date: -->"<<endl;
		is>>date;
		cout<<"Control (Exam = 1, Offset = 2): -->"<<endl;
		is>>control;
		return is;
	}

Seminar::Seminar () 
	{
		quantity = 1;
		control = 1; 
		date = 1;
	};

Seminar* Seminar::clone() const
	{
	return new Seminar(*this);
	}

int Seminar::getdate () const
	{
		return date;
	}

int Seminar::setdate (int n)
	{
		if (n>16||n<0) { throw exception ("Date must be pozitive and less then 16");}
		date = n;
		return 1;
	}

Laboratory::Laboratory()
{
	duration = 13;
	date = 10;
	quan_lab = 1;
	lab[0].capacity=15;
	lab[0].index=1;
	quantity = 16;

}

Laboratory* Laboratory::clone() const
	{
		return new Laboratory(*this);
	}

int Laboratory::getdate () const
	{
		return date;
	}

int Laboratory::setdate (int n)
	{
		if (n>16||n<0) { throw exception ("Date must be pozitive and less then 16"); return -1;}
		date = n;
		return 1;
	}

int Laboratory::setduration (int n)
{
	if (n<0||n>8) {throw exception ("Sam stol'ko labu delay! >< Wrong duration"); return -1;}
	duration = n;
	return 1;
}

int Laboratory::getduration() const
{
	return duration;
}

int Laboratory::setquanlab(int n)
{
	if (n<0||n>3){ throw exception ("Quantity must be pozitive and less or equal 3"); return -1;}
	quan_lab = n;
	return 1;
}

int Laboratory::getquanlab() const
{
	return quan_lab;
}

int Laboratory::setIndex (int n, int ind)
{
	if (n<0||n>3||ind<=0){ throw exception ("Wrong index"); return -1;}
	lab[n].index=ind;
	return 1;
}

int Laboratory::getIndex (int n) const
{
	if (n<0||n>3){ throw exception ("Wrong index"); return -1;}
	return lab[n].index;
}

int Laboratory::setCapacity (int n, int cap)
{
	lab[n].capacity=cap;
	return 1;
}

int Laboratory::getCapacity(int n) const
{
	return lab[n].capacity;

}
ostream& Laboratory::show(ostream& os)const
{	
	LessonType::show(os);
	os<<"				Laboratories:"<<endl;
	for (int i=0;i<quan_lab;i++) os<<"				Index: "<<lab[i].index<<" Capacity: "<<lab[i].capacity<<endl;	
	return os <<"				Date: " << date <<"\n				Duration: "<<duration;
}

 istream& Laboratory::get(istream& is) 
 {
	cout<<"Quanity:"<<endl;
	LessonType::get(is);
	cout<<"Date for beginning:"<<endl;
	is>>date;
	cout<<"Put quantity of laboratories:"<<endl;
	is>>quan_lab;
	for (int i=0;i<quan_lab;i++) {
	cout<<"Index:"<<endl;
	is>>lab[i].index;
	cout<<"Capacity:"<<endl;
	is>>lab[i].capacity;
	}
	cout<<"Duration:"<<endl;
	return is>>duration;
 }

 
Subject:: Subject(const string &s, LessonType* const p [], int n)
 { 
	name = s;
	kol = n;
	for (int i = 0; i < kol; ++i)
    ptr[i] = p[i]->clone();
 }

Subject::Subject ()
	 {
		name="";
		kol = 0; 
		
	     for (int i = 0; i < 3; ++i)
		 ptr[i] = NULL;
	 }

Subject:: ~Subject () 
	 {
		 for (int i = 0; i < kol; i++)
		 {
			 ptr[i]=NULL;
			 	 delete ptr[i];
		 }
	 }

int Subject::setSub (const string &s, int kol1)
{
	name = s; 
	kol = kol1;
	Lection lec;
	Seminar sem;
	Laboratory lab;
	LessonType* tmp;
	int ans;
	int flag = 0;
	for (int i = 0; i < kol; i++)
	{
		cout<<"Make your choice -->"<<endl;
		cout<<"1. Lection\n2. Seminar\n3. Laboratory"<<endl;
		cin>>ans;
		switch (ans)
		{
		case 1:
			if (i != 0)
				for (int z = 0; z < kol; z++)
				{
				if (ptr[z]!= NULL)
					if (ptr[z]->type() == 1)
					{
						flag = 1;
					}
				}
				if (flag == 1) {flag = 0; i = i-1; cout<<"You can't add more lections!"<<endl; break;}
			tmp = &lec;
			cin>>(*tmp);
			ptr[i] = tmp->clone();
			break;
		case 2:
			if (i != 0)
				for (int z = 0; z < kol; z++)
				{
				if (ptr[z]!= NULL)
					if (ptr[z]->type() == 2)
					{
						flag = 1;
					}
				}
				if (flag == 1) {flag = 0; i = i-1; cout<<"You can't add more seminars!"<<endl; break;}
			tmp = &sem;
			cin>>(*tmp);
			ptr[i] = tmp->clone();
			break;
		case 3:
			if (i != 0)
				for (int z = 0; z < kol; z++)
				{
				if (ptr[z]!= NULL)
					if (ptr[z]->type() == 3)
					{
						flag = 1;
					}
				}
				if (flag == 1) {flag = 0; i = i-1; cout<<"You can't add more labs!"<<endl; break;}
			tmp = &lab;
			cin>>(*tmp);
			ptr[i] = tmp->clone();
			break;
		}
	
	}
	return 1;
}