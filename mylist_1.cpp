#include<iostream>
using namespace std;

class PopEmptyArray
{	private:
		const char *message;
	public:
		PopEmptyArray(): message("Exception occured: Cannot pop an empty array.") {}
		const char *what() const {return message;}
};

class SubscriptException
{	private:
		const char *message;
	public:
		SubscriptException(): message("Exception occured: Subscript is out of range.") {}
		const char *what() const {return message;}
};

template<class T>
class MyList{
private:
	T *a;
	int numb;
	int size;
	
	void double_space() //double the space when it is not enough for the array.
	{	T *b;
		size *= 2;
		b = new T[size];
		for (int i=0; i<numb; ++i)
			b[i] = a[i];
		a = b;
	}
	
	void Qsort_1(T a[], int low, int high) //ascending quick sort.
	{	int first = low;
		int last = high;
		T key = a[(low+high)/2];
		T mid;
		
		while (first<=last)
		{	while (a[first]<key)
				++first;
			while (a[last]>key)
				--last;
			if (first<=last)
			{	mid = a[first];
				a[first] = a[last];
				a[last] = mid;
				++first;
				--last;
			}
		}
		
		if (first<high)
			Qsort_1(a, first, high);
		if (last>low)
			Qsort_1(a, low, last);
	}
	
	void Qsort_2(T a[], int low, int high) //descending quick sort.
	{	int first = low;
		int last = high;
		T key = a[(low+high)/2];
		T mid;
		
		while (first<=last)
		{	while (a[first]>key)
				++first;
			while (a[last]<key)
				--last;
			if (first<=last)
			{	mid = a[first];
				a[first] = a[last];
				a[last] = mid;
				++first;
				--last;
			}
		}
		
		if (first<high)
			Qsort_2(a, first, high);
		if (last>low)
			Qsort_2(a, low, last);
	}
	
public:
	MyList()
	{	numb = 0; 
		size = 100;
		a = new T[size];
	}
	MyList(int num, const T &item) //repeat 'item' for 'num' times and put then into the array.
	{	numb = num;
		size = 2*numb;
		a = new T[size];
		for (int i=0; i<numb; ++i)
			a[i] = item;
	}
	MyList(const MyList &l) //copy another 'MyList'.
	{	numb = l.get_size();
		size = 2*numb;
		a = new T[size];
		for (int i=0; i<numb; ++i)
			a[i] = l.a[i];
	}
    MyList(T *arr, int len) //put the first 'len' items of 'arr' into a new array.
    {	numb = len;
    	size = 2*numb;
    	a = new T[size];
    	for (int i=0; i<numb; ++i)
    		a[i] = arr[i];
	}

	void push(const T &item) //put item at the bottom of MyList.
	{	while (size<=numb)
			double_space();
		a[numb++] = item;
	}
	T pop() //delete the last item in MyList and return it.
	{	try
		{	if (numb==0)
				throw PopEmptyArray();
			return a[--numb];
		}
		catch (PopEmptyArray ex) {cout << ex.what() <<endl; exit(-1);}
	}
	void insert(int place, const T &item) //put item at place.
	{	try
		{	if (place<0)
			{	if (place+numb<0)
					throw SubscriptException();
				insert(place+numb+1, item);
			}
			else
			{	if (place>=numb)
					throw SubscriptException();
				else
				{	while (size<=numb)
						double_space();
					for (int i=numb; i>place; --i)
						a[i] = a[i-1];
					a[place] = item;
					
					++numb;
				}
			}
		}
		catch (SubscriptException ex) {cout << ex.what() <<endl; exit(-1);}
	}
	void clean() //claer the array.
	{	numb = 0;
		size = 100;
	}
	int get_size()const //return the number of items in array.
	{	return numb;
	}
	void erase(int start, int end) //delete the items from 'start' to 'end'(sides included).
	{	try
		{	if (start>=0&&end>=0)
			{	if (start>=numb || end>=numb)
					throw SubscriptException();
				else
				{	if (start>end)
						erase(end, start);
					else
					{	for (; end<numb; ++start, ++end)
							a[start] = a[end+1];
						numb -= end-start+1;
					}
				}
			}
			else if (start>=0&&end<0)
			{	if (start>=numb || end+numb<0)
					throw SubscriptException();
				else
				{	if (start>end+numb)
						erase(end+numb, start);
					else
						erase(start, end+numb);
				}
			}
			else if (start<0&&end>=0)
			{	if (start+numb<0 || end>=numb)
					throw SubscriptException();
				else
				{	if (start+numb>end)
						erase(end, start+numb);
					else
						erase(start+numb, end);
				}
			}
			else
			{	if (start+numb<0 || end+numb<0)
					throw SubscriptException();
				else
				{	if (start>end)
						erase(end+numb, start+numb);
					else
						erase(start+numb, end+numb);
				}
			}
		}
		catch (SubscriptException ex) {cout << ex.what() <<endl; exit(-1);}
	}
	T get_item(int index) // return the 'index'th item.
	{	try
		{	if (index<0)
			{	if (index+numb<0)
					throw SubscriptException();
				get_item(index+numb);
			}
			else
			{	if (index>=numb)
					throw SubscriptException();
				return a[index];
			}
		}
		catch (SubscriptException ex) {cout << ex.what() <<endl; exit(-1);}
	}
	MyList get_item(int start, int end) //return the items from 'start' to 'end'(sides included)(negative numbers are accepted)
	{	try
		{	MyList<T> b;
			if (start>=0&&end>=0)
			{	if (start>=numb || end>=numb)
					throw SubscriptException();
				else
				{	if (start>end)
						return b;
					else
					{	b.numb = end-start+1;
						while (b.size<=b.numb)
							b.double_space();
						for (int i=start; i<=end; ++i)
							b.a[i-start] = a[i];
						return b;
					}
				}
			}
			else if (start>=0&&end<0)
			{	if (start>=numb || end+numb<0)
					throw SubscriptException();
				else
				{	if (start>end+numb)
						return b;
					else
						return get_item(start, end+numb);
				}
			}
			else if (start<0&&end>=0)
			{	if (start+numb<0 || end>=numb)
					throw SubscriptException();
				else
				{	if (start+numb>end)
						return b;
					else
						return get_item(start+numb, end);
				}
			}
			else
			{	if (start+numb<0 || end+numb<0)
					throw SubscriptException();
				else
				{	if (start>end)
						return b;
					else
						return get_item(start+numb, end+numb);
				}
			}
		}
		catch (SubscriptException ex) {cout << ex.what() <<endl; exit(-1);}
	}
	int count(const T &item) //return the number of the items that are equal to 'item' in MyList.
	{	int cnt=0;
		for (int i=0; i<numb; ++i)
		{	if (a[i]==item)
				++cnt;
		}
		return cnt;
	}
	void remove(const T &item) //delete the first item that is equal to 'item' in MyList.
	{	bool flag=0;
		for (int i=0; i<numb; ++i)
		{	if (a[i]==item)
			{	for (int j=i; j<numb-1; ++j)
					a[j] = a[j+1];
				flag = 1;
				break;
			}
		}
		if (flag)
			--numb;
	}

	friend MyList operator + (const MyList &l1, const MyList &l2) //merge two lists.
	{	MyList<T> tmp(l1);
		int l1_n, l2_n;
		l1_n = l1.get_size();
		l2_n = l2.get_size();
		tmp.numb = l1_n+l2_n;;
		while (tmp.size<l1_n+l2_n)
			tmp.double_space();
		for (int i=l1_n; i<l1_n+l2_n; ++i)
			tmp.a[i] = l2.a[i-l1_n]; 
		return tmp;
	}
    friend MyList operator + (const MyList &l1, const T &item) //similar to 'push'.
    {	MyList<T> tmp(l1);
		tmp.push(item);
		return tmp; 
	}
	MyList &operator = (const MyList &l) //assignment.
	{	numb = l.numb;
		size = l.size;
		for (int i=0; i<numb; ++i)
			a[i] = l.a[i];
		return *this;
	}
	MyList &operator += (const T &item) //same to push(T item).
	{	while (size<=numb)
			double_space();
		push(item);
		return *this;
	}
	MyList &operator += (const MyList &l) //add another array to the previous one.
	{	while (size<=numb+l.numb)
			double_space();
		for (int i=numb; i<numb+l.numb; ++i)
			a[i] = l.a[i-numb];
		numb = numb+l.numb;
		return *this;
	}
	T &operator [](int index) //return the 'index'th item.
	{	try
		{	if (index<0)
			{	if (index+numb<0)
					throw SubscriptException();
				return a[index+numb];
			}
			else
			{	if (index>=numb)
					throw SubscriptException();
				return a[index];
			}
		}
		catch (SubscriptException ex) {cout << ex.what() <<endl; exit(-1);}
	}
	friend ostream & operator<<(ostream &os, const MyList &obj) //output.
    {	if (obj.numb==0)                                       
    		os << "[]";
    	else
		{	os << '[';
			for (int i=0; i<obj.numb-1; ++i)
    			os << obj.a[i] << ", ";
			os << obj.a[obj.numb-1] << ']';
		}
    	return os;
	}
	
	void sort(bool less=true) //sort.
	{	if (less)
			Qsort_1(a, 0, numb-1);
		else
			Qsort_2(a, 0, numb-1);
	}
    // If less=true£¬ascending.
	// Otherwise, descending.
	void reverse() //reverse the array.
	{	int first = 0;
		int last = numb-1;
		T mid;
		
		while (first<=last)
		{	mid = a[first];
			a[first] = a[last];
			a[last] = mid;
			++first;
			--last;
		}
	}

	~MyList() {delete [] a;}
};

int main()
{	MyList<int> a, b, z;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4] //bingo
    
    cout << "[] test:" <<endl;
    /*z = a; //save a to test subscript
    for (int j=-a.get_size()-1; j<a.get_size()+1; ++j)
    	cout << a[j] <<endl;
	a = z; //give it back*/
	
	a[3] = 15; // a = [0, 1, 2, 15, 4] //bingo
	a.sort(); // a = [0, 1, 2, 4, 15] //bingo
	a.reverse(); // a = [15, 4, 2, 1, 0] //bingo
	a += 12; // a = [15, 4, 2, 1, 0, 12] //bingo
	
	cout << "\npop test:" <<endl;
	/*z = a; //save a to test pop
	int a_size = a.get_size();
	for (int j=0; j<a_size+1; ++j)
		cout << "pop:" << a.pop() <<endl;
	cout << a <<endl; //a should be empty
	a = z; //give it back*/
	
	cout << "\na:" <<endl;
	for (i=0; i<a.get_size(); ++i) //bingo
		cout<<a[i]<<endl;
	
	cout << "\nget_item test:" <<endl;
	/*cout << a.get_item(100)<<endl;
	b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é //bingo
    cout << b <<endl;
	b = a.get_item(2,100);
	b = a.get_item(-99, -1);*/
	b = a.get_item(3, -1); // b = [1, 0, 12] //bingo
	cout << b <<endl;
	
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12] //bingo
	
	cout << "\na:" <<endl;
	for (i=0; i<a.get_size(); ++i) //bingo
		cout<<a.get_item(i)<<endl;
	
	cout << "\ncount for '5' in a:" <<endl;
	cout<<a.count(5)<<endl; //bingo
	cout << "count for '12' in a:" <<endl;
	cout<<a.count(12)<<endl;
	
	b.clean(); // b = [] //bingo
	
	cout << "\nb.get_size() = ";
	cout<<b.get_size()<<endl; //bingo
	
	cout << "\nerase test:" <<endl;
	cout << a <<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12] //bingo
	cout << a <<endl;
	/*z = a;
	a.erase(3, 2);
	cout << a <<endl;
	a.erase(0, 100);
	cout << a <<endl;
	a.erase(-88, -2);
	cout << a <<endl;
	a = z;*/
	
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12] //bingo
	
	cout << "\ninsert test:" <<endl;
	cout << b <<endl;
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12] //bingo
	cout << b <<endl;
	/*z = b;
	b.insert(-4, 232);
	cout << b <<endl;
	b.insert(100,100);
	cout << b << endl;
	b.insert(-66, 123);
	cout << b <<endl;
	b = z;*/
	
	b.remove(4); // b = [15, 1, 116, ...] //bingo
	
	cout << "\nb = ";
	cout<<b<<endl; //bingo
	
	MyList<double> c(10, 3.14); //bingo
	for (i=0; i<100; ++i) //bingo
		c.push(1.1*i);
	cout << "\nc.get_item(100,105) = ";
	cout<<c.get_item(100, 105)<<endl; //bingo
	
	return 0;
}
