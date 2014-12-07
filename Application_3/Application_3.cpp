// Application_3.cpp: определяет точку входа для консольного приложения.
//
#include "..\Library_3\Template.h"
#include "stdafx.h"
#include "..\Library_3\LessonType.h"
#include <iostream>
#include <string>
#include "..\Library_3\Assoc.h"

const char *Names[] = {"Uknown", "***Lection***", "***Seminar***", "***Laboratory***"};
const char *Names2[] = {"Uknown", "Lection", "Seminar", "Laboratory"};
const char *Menu[] = {"1. Add a subject", "2. Find a subject",
					  "3. Delete a subject", "4. Show all table", "5. Change smth in the subject", "6. Total quantity of hours", "0. Quit"},
		   *Choice = "Make your choice", 
		   *Msg = "You are wrong; repeate please";

int Answer(const char *alt[], int n);
int Add(Assoc &), Find(Assoc &), Delete (Assoc &), ShowAll(Assoc &), Change(Assoc &), Total (Assoc &);
int (*Funcs[])(Assoc &) = {NULL, Add, Find, Delete, ShowAll, Change, Total};

const int Num = sizeof(Menu)/sizeof(Menu[0]);


void main()
{
	Assoc ar;
	int ind;
	while(ind = Answer(Menu, Num))
		Funcs[ind](ar);
	cout << "That's all. Buy!" << endl;
}

int Answer(const char *alt[], int n)
{
	int answer;
	const char *prompt = Choice;
	cout << "What do you want to do:" << endl;
	for(int i = 0; i < n; i++)
		cout << alt[i] << endl;
	do{
		cout << prompt << ": -> ";
		prompt = Msg;
		cin >> answer;
	} while(answer < 0 || answer >= n);
	cin.ignore(80, '\n');
	return answer;
}

int Add(Assoc &a)
{
	int code=0;
	string name;
	LessonType *ptr = nullptr;
	Seminar sem;
	Lection lec;
	Laboratory lab;
	int j;
		cout << "Enter a subject code: --> ";
		cin>>code;
		cout << "Enter a subject name: --> ";
		cin >> name;
		cout << "Enter how many different lesson types will be used -->";
		cin>>j;
		if (j>3) {cout<<"Only 3 lesson types!"<<endl; return 0;}
		Subject k;		
		k.setSub(name, j);
		try {
     	a.insert(code, k);	 
		}
		catch (exception &e) {e.what();};
	return 0;
}


int Find(Assoc &a)
{
	int code;
	AssocIt it;
	LessonType *ptr[3];
	for (int i = 0; i<3 ; ++i)
		ptr[i]=NULL;
	cout << "Enter a subject code: --> ";
	cin >> code;
	it = a.find(code);
	if(it == a.end()){
		cout << "The subject with code \"" << code << "\" is absent in container"
			<< endl;
		return -1;
	}
	cout<<"				Subject: "<<(*it).second.name<<endl;
	for (int i = 0; i<(*it).second.kol; ++i) 
	{
		ptr[i] = (*it).second.ptr[i];
		cout<<"				"<<Names[ptr[i]->type()]<<": "<<endl;
		cout<<"				";
		cout<<*ptr[i]<<endl;
	}
	return 0;
}

int ShowAll(Assoc &a)
{
	AssocIt it;
	cout<<"Code		Name		Lesson types		"<<endl;
	for(it = a.begin(); it != a.end(); ++it)
	{   
		if ((*it).second.ptr[0]!=nullptr)
		{
		cout << (*it).first;
		cout<< "		"<< (*it).second.name;
		
		for (int i = 0; i < (*it).second.kol; i++)
			{
				if (i == 0) {
				cout <<"		" << Names[(*it).second.ptr[i]->type()]<<endl;
				cout<<"				"<<*((*it).second.ptr[i])<<endl;
				}
				if (i != 0)
				{
				cout <<"				"<<Names[(*it).second.ptr[i]->type()]<<endl;
				cout<<"				"<<*((*it).second.ptr[i])<<endl;
				}
			}
		cout<<endl;
		}
	}
	return 0;
}


int Delete (Assoc &a)
{
	int code;
	AssocIt it;
	cout << "Enter a subject code: --> ";
	cin >> code;
	it = a.find(code);
	if(it == a.end())
		cout << "The subject with code \"" << code << "\" is absent in container" << endl;
	else 
	{
	  a.deletef(code);	
	}
	return 1;
}

int Change(Assoc &a)
{
	int code;
	AssocIt it;
	cout << "Put the code of subject you want to change"<<endl;
	cin>>code;
	int ans, ans2;
	Lection lec;
	LessonType* tmp = &lec;

	it = a.find(code);
	if(it == a.end())
		cout << "The subject with code \"" << code << "\" is absent in container" << endl;
	else 
	{ 
		cout<<"1. Change the structure of the subject\n2. Change smth in the lesson type"<<endl;
		cin>>ans;
		switch (ans)
		{
		case 1:
			a.change(code);
			break;
		case 2: 
			for (int i = 0; i < (*it).second.kol; i++)
				{
					cout<<(*it).second.ptr[i]->type()<<". "<<Names2[(*it).second.ptr[i]->type()]<<endl;
				}
			cin>>ans2;
			switch(ans2)
			{
			case 1: 
				a.change_lec(code);
				break;
			case 2:
				a.change_sem(code);
			case 3:
				a.change_lab(code);
			}
		}
	}
	return 0;
}

int Total (Assoc &a)
{
	AssocIt it;
	int k = 0;
	int z = 0;
	for (it = a.begin(); it != a.end(); ++it)
	{
		k = 0;
		for (int i = 0; i <(*it).second.kol; i++)
		{
			k = (*it).second.ptr[i]->getquan()+k;
		}
		z = z + k;
		cout<<"***Total hours for \""<<(*it).second.name<<"\" *** : "<<k<<endl;
	}
	cout<<"***Hours for all subjects*** : "<<z<<endl;
	return 0;
}
