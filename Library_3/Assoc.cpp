#include "StdAfx.h"
#include "Assoc.h"

using namespace std;

Assoc::Assoc(/*const*/ Assoc &a)
{
	Mymap</*const*/ int, Subject>::/*const_*/Iterator p;
	for (p = a.arr.begin(); p != a.arr.end(); ++p)
		arr.insert((*p).first, (*p).second); 
}

Assoc::~Assoc()
{
	Mymap</*const*/ int, Subject>::Iterator p;
	for (p = arr.begin(); p != arr.end(); ++p)
	{
		(*p).second.kol = 0;
		for (int i = 0; i < (*p).second.kol; ++i)
		{
			delete (*p).second.ptr[i];
			(*p).second.ptr[i] = nullptr;
		}
	}
}


Assoc& Assoc::operator = (/*const*/ Assoc &a)
{
	Mymap</*const*/ int, Subject>::Iterator p;
	if (this != &a)
	{
		for (p = arr.begin(); p != arr.end(); ++p)
			delete (*p).second.ptr;
		arr.clear();
		Mymap</*const*/ int, Subject>::/*const_*/Iterator pp;
		for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
			for (int i=0; i<3;i++)
				arr.insert((*p).first, (*p).second);
	}
	return *this;
}

void Assoc::insert(const int s, const Subject f)
{
  Mymap<int, Subject>::Iterator p = arr.find(s);
   if (p == arr.end())
		arr.insert(s, f);
   else
		for (int i = 0; i < (*p).second.kol; ++i)
		{
			delete (*p).second.ptr[i];
			(*p).second.ptr[i] = NULL;
		}
		(*p).second.name = f.name;
		for (int i = 0; i < f.kol; i++)
		{
			(*p).second.ptr[i] = f.ptr[i]->clone();
		(*p).second.kol = f.kol;
		}
}

Assoc::Iterator Assoc::find(int s)
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	return AssocIt(p);
}

Assoc::Iterator Assoc::begin()
{
	return AssocIt(arr.begin());
}

Assoc::Iterator Assoc::end()
{
	return AssocIt(arr.end());
}

void Assoc::deletef(const int s)
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	if (p!=arr.end())
	{
		(*p).second.kol=0;
		for (int i = 0; i<(*p).second.kol; ++i)
		{
			delete (*p).second.ptr[i];
			(*p).second.ptr[i] = nullptr;
		}
		(*p).second.ptr[0] = nullptr;
		//arr.erase(s);
	}
};

void Assoc::change_lec (const int s) 
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	int q;
	if (p!=arr.end())
	{	
		cout<<"Input new hours quantity"<<endl;
		cin>>q;

		for (int i = 0; i <(*p).second.kol; ++i)
		{
			if ((*p).second.ptr[i]->type() == 1)
			{
				try {
				(*p).second.ptr[i]->setquan(q);
				}
				catch (exception &e) {e.what();};
			}
		}
	
	}
}

void Assoc::change_sem (const int s) 
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	int q;
	if (p!=arr.end())
	{
		cout<<"Input new hours quantity"<<endl;
		cin>>q;

		for (int i = 0; i <(*p).second.kol; ++i)
		{
			if ((*p).second.ptr[i]->type() == 2)
			{
				try{
				(*p).second.ptr[i]->setquan(q);
				}
				catch (exception &e) {e.what();};

			}
		}
	}
}

void Assoc::change_lab (const int s) 
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	int ans, ans2, ind, cap;
	Laboratory* ppt;
	if (p!=arr.end())
	{
		for (int i = 0; i < (*p).second.kol; i++)
		{
			if ((*p).second.ptr[i]->type() == 3)
			{
				ppt = dynamic_cast<Laboratory*>((*p).second.ptr[i]);
				cout<<"What do you want to change?"<<endl;
				cout<<"1. Change duration\n2. Change quantity of laboratories\n3. Change index of laboratory\n4. Change capacity of the laboratory"<<endl;
				cin>>ans;
				switch(ans) 
				{
				case 1:
					cout<<"Input new duration -->"<<endl;
					cin>>ans2;
				    ppt->setduration(ans2);
					break;
				case 2:
					cout<<"Input new quantity of laboratories -->"<<endl;
					cin>>ans2;
					ppt->setquanlab(ans2);
					for (int i = 0; i < ans2; ++i)
					{
						cout<<"Input new index -->"<<endl;
						cin>>ind;
						ppt->setIndex(i, ind);
						cout<<"Input new capacity -->"<<endl;
						cin>>cap;
						ppt->setCapacity(i, cap);
					}
					break;
				case 3:
					cout<<"Input number of laboratory index you wanna change -->"<<endl;
					cin>>cap;
					cout<<"Input new index -->"<<endl;
					cin>>ind;
					ppt->setIndex(cap-1, ind);
					break;
				case 4:
					int flag = 1;
					cout<<"Input index of laboratory capacity you wanna change -->"<<endl;
					cin>>ind;
					int z;
					int i = 0;
					for (int i = 0; i < ppt->getquanlab(); i++)
					{
						z = ppt->getIndex(i);
						if (z == ind)
						{
							cout<<"Input new capacity -->"<<endl;
							cin>>cap;
							ppt->setCapacity(i, cap);
							flag = 0;
						}
					}
						if (flag == 1 ) cout<<"There is now such index"<<endl;
					break;
				}
			}

		}
		
	}
}

void Assoc::change (const int s)
{
	Mymap</*const*/ int, Subject >::Iterator p = arr.find(s);
	int kolvo;
	cout<<"How many lesson types you want to add?"<<endl;
	cin>>kolvo;
	for (int i = 0; i < (*p).second.kol; i++)
	{
		delete (*p).second.ptr[i];
		(*p).second.ptr[i]=NULL;
	
	}
	(*p).second.setSub((*p).second.name, kolvo);
}
// Методы класса AssocIt

int Assoc::Iterator::operator !=(const AssocIt &it) const
{
	return cur != it.cur;
}

int AssocIt::operator ==(const AssocIt &it) const
{
	return cur == it.cur;
}

Pair</*const*/ int, Subject> & AssocIt::operator *()
{
	return *cur;
}

AssocIt & AssocIt::operator ++()
{
	++cur;
	return *this;
}

AssocIt AssocIt::operator ++(int)
{
	AssocIt res(*this);
	++cur;
	return res;
}
