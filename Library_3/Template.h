#include <iostream>
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_
using namespace std;
/*!<Hello! I am testng the doxygen. You can see my lab for syllabus (u4ebniy plan po-ruuski)*/
template <class IND, class INF>
struct Pair{
	IND first;
	INF second;
	Pair():first(IND()),second(INF()){}
};


template <class IND, class INF>
const Pair<IND, INF> make_pair(const IND& s, const INF &p)
{
	return Pair<IND, INF>(s, p);
}

template <class IND, class INF>
class MymapIt;

template <class IND, class INF>
class Mymap{
	friend class MymapIt<IND, INF>;
private:
	static const int QUOTA = 1;
	int cnt;
	Pair <IND, INF> *arr;
	int maxsz;
public:
	int check (const IND &) const;
	typedef MymapIt<IND, INF> Iterator;
	Mymap() :maxsz(QUOTA), cnt(0), arr(new Pair<IND, INF>[QUOTA]){}
	Mymap(const Mymap<IND, INF> &);
	~Mymap(){delete [] arr;}
	Mymap<IND, INF>& operator = (const Mymap<IND, INF> &);
	void insert(const IND&, const INF&);
	void clear(){ delete[] arr; }
	Iterator find(const IND&);
	Iterator begin();
	Iterator end();
};

template <class IND, class INF>
MymapIt<IND, INF> Mymap<IND, INF>::begin() 
{
	return MymapIt<IND, INF>(*this);
}


template <class IND, class INF>
MymapIt<IND, INF> Mymap<IND, INF>::end() 
{
	return MymapIt<IND, INF>(*this, cnt);
}

template <class IND, class INF>
Mymap<IND, INF>::Mymap(const Mymap<IND, INF> &t) :maxsz(t.maxsz), cnt(t.cnt)
{
	arr = new Pair<IND, INF> [maxsz];
	for(int i = 0; i < cnt; i++)
	{
		arr[i].first = t.arr[i].first;
		arr[i].second = t.arr[i].second;
	}
}


template <class IND, class INF>
Mymap<IND, INF>& Mymap<IND, INF>::operator = (const Mymap<IND, INF> &a)
{
	if(this != &a){
		delete [] arr;
		maxsz = a.maxsz;
		arr = new Pair <IND, INF> [maxsz];
		cnt = a.cnt;
		for(int i = 0; i < cnt; i++)
		{
			arr[i].first = a.arr[i].first;
			arr[i].second = arr[i].second;
		}
	}
	return *this;
}

template <class IND, class INF>
int Mymap<IND, INF>::check(const IND &s) const
{
	for(int i = 0; i < cnt; ++i)
		if(arr[i].first == s)
			return i;
	return -1;
}

template <class IND, class INF>
void Mymap<IND, INF>::insert (const IND &s, const INF &f)
{
	int i = check(s);
	if (i < 0)
	{
		if (cnt == maxsz)
		{
			Pair <IND, INF> *old = arr;
			arr = new Pair <IND, INF> [maxsz+=QUOTA];
			for (int i = 0; i < cnt; i++)
				arr[i] = old[i];
			delete[] old;
		}
		arr[cnt].first = s;
		arr[cnt].second = f;
		cnt++;
	}
	else
	arr[cnt].second = f;
}

template <class IND, class INF>
MymapIt<IND, INF> Mymap<IND, INF>::find(const IND &s)
{
	for(int i = 0; i < cnt; ++i)
		if(arr[i].first == s)
			return MymapIt<IND, INF>(*this, i); 
		return MymapIt<IND, INF>(*this, cnt);
}

// -------- template class MymapIt ----------------
template <class IND, class INF>
class MymapIt{
private:
	Mymap<IND, INF> *pAs;
	int cur;
public:
	MymapIt(Mymap<IND, INF> &as, int last = 0):pAs(&as), cur(last){}
	MymapIt():pAs(NULL),cur(0){}
	Pair<IND, INF>& operator *();
	MymapIt<IND, INF>& operator ++();
	MymapIt<IND, INF> operator ++(int);
	int operator !=(const MymapIt<IND, INF> &) const;
	int operator ==(const MymapIt<IND, INF> &) const;
};

template <class IND, class INF>
Pair<IND, INF>& MymapIt<IND, INF>::operator *()
{
	return pAs->arr[cur];
}

template <class IND, class INF>
MymapIt<IND, INF>& MymapIt<IND, INF>::operator ++()
{
	++cur;
	return *this;
}

template <class IND, class INF>
MymapIt<IND, INF> MymapIt<IND, INF>::operator ++(int)
{
	MymapIt r(*this);
	++cur;
	return r;
}

template <class IND, class INF>
int MymapIt<IND, INF>::operator !=(const MymapIt<IND, INF> &a) const
{
	return pAs != a.pAs || cur != a.cur;
}

template <class IND, class INF>
int MymapIt<IND, INF>::operator ==(const MymapIt<IND, INF> &a) const
{
	return pAs == a.pAs && cur == a.cur;
}


// -------- template class const_MymapIt ----------------
template <class IND, class INF>
class const_MymapIt{
private:
	const Mymap<IND, INF> *pAs;
	int cur;
public:
	const_MymapIt(const Mymap<IND, INF> &as, int last = 0) :pAs(&as), cur(last){}
	const_MymapIt() :pAs(NULL), cur(0){}
	const Pair<IND, INF>& operator *() const;
	const_MymapIt<IND, INF>& operator ++();
	const_MymapIt<IND, INF> operator ++(int);
	int operator !=(const const_MymapIt<IND, INF> &) const;
	int operator ==(const const_MymapIt<IND, INF> &) const;
};

template <class IND, class INF>
const Pair<IND, INF>& const_MymapIt<IND, INF>::operator *() const
{
	return pAs->arr[cur];
}

template <class IND, class INF>
const_MymapIt<IND, INF>& const_MymapIt<IND, INF>::operator ++()
{
	++cur;
	return *this;
}

template <class IND, class INF>
const_MymapIt<IND, INF> const_MymapIt<IND, INF>::operator ++(int)
{
	const_MymapIt r(*this);
	++cur;
	return r;
}

template <class IND, class INF>
int const_MymapIt<IND, INF>::operator !=(const const_MymapIt<IND, INF> &a) const
{
	return pAs != a.pAs || cur != a.cur;
}

template <class IND, class INF>
int const_MymapIt<IND, INF>::operator ==(const const_MymapIt<IND, INF> &a) const
{
	return pAs == a.pAs && cur == a.cur;
}
#endif
