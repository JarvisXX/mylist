/*
 * 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
 * 必须使用template <class T>，不允许使用<iostream>以外的库。
 * 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
 * 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
 * 请使用try-catch-throw处理错误。
 * 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
 */

/* 
 * 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
 */

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
		delete [] b;
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

	void push(const T &item)//将item添加在MyList最后。
	{	while (size<=numb)
			double_space();
		a[numb++] = item;
	}
	T pop()//将MyList中最后一个元素删除，并返回这个删除的元素。
	{	if (numb==0)
			throw PopEmptyArray();
		return a[--numb];
	}
	void insert(int place, const T &item)//将item插入到place处。
	{	if (place<0)
			insert(place+numb, item);
		else
		{	while (size<=numb)
				double_space();
			for (int i=numb; i>place; --i)
				a[i] = a[i-1];
			a[place] = item;
			++numb;
		}
	}
	void clean()//清空数组。
	{	numb = 0;
		size = 100;
	}
	int get_size()const//返回MyList中元素的数量。
	{	return numb;
	}
	void erase(int start, int end)//删除MyList中第start到第end位的元素，包括两边。
	{	for (; end<numb; ++start, ++end)
			a[start] = a[end+1];
		numb -= end-start+1;
	}
	T get_item(int index)//返回第index个元素。
	{	return a[index];
	}
	MyList get_item(int start, int end)//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
	{	MyList b;
		if (start>=0&&end>=0)
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
		else if (start>=0&&end<0)
		{	if (start>end+numb)
				return b;
			else
				return get_item(start, end+numb);
		}
		else if (start<0&&end>=0)
		{	if (start+numb>end)
				return b;
			else
				return get_item(start+numb, end);
		}
		else
		{	if (start>end)
				return b;
			else
				return get_item(start+numb, end+numb);
		}
	}
	int count(const T &item)//返回MyList中和item相等的元素的个数。
	{	int cnt=0;
		for (int i=0; i<numb; ++i)
		{	if (a[i]==item)
				++cnt;
		}
		return cnt;
	}
	void remove(const T &item)//删除MyList中第一个和item相等的元素。
	{	for (int i=0; i<numb; ++i)
		{	if (a[i]==item)
			{	for (int j=i; j<numb-1; ++j)
				{	a[j] = a[j+1];
				}
				break;
			}
		}
		--numb;
	}

	friend MyList operator + (const MyList &l1, const MyList &l2)//合并两个MyList
	{	MyList tmp(l1);
		int l1_n, l2_n;
		l1_n = l1.get_size();
		l2_n = l2.get_size();
		tmp.numb = l1_n+l2_n;
		while (tmp.size<l1_n+l2_n)
			tmp.double_space();
		for (int i=l1_n; i<l1_n+l2_n; ++i)
			tmp.a[i] = l2.a[i-l1_n]; 
		return tmp;
	}
    friend MyList operator + (const MyList &l1, const T &item)//同push(T item)，但不修改l1，返回一个新数组
    {	MyList tmp(l1);
		tmp.push(item);
		return tmp; 
	}
	MyList &operator = (const MyList &l)//赋值
	{	numb = l.numb;
		size = l.size;
		for (int i=0; i<numb; ++i)
			a[i] = l.a[i];
		return *this;
	}
	MyList &operator += (const T &item)//同push(T item)
	{	while (size<=numb)
			double_space();
		push(item);
		return *this;
	}
	MyList &operator += (const MyList &l)//将一个MyList加入到本个MyList之后。
	{	while (size<=numb+l.numb)
			double_space();
		for (int i=numb; i<numb+l.numb; ++i)
			a[i] = l.a[i-numb];
		numb = numb+l.numb;
		return *this;
	}
	T &operator [](int index)//返回第index个元素。
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
	friend ostream & operator<<(ostream &os, const MyList &obj)//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
    {	if (obj.numb==0)                                       // [1, 2, 5, 4, 1]
    		os << "[]";
    	else
		{	os << '[';
			for (int i=0; i<obj.numb-1; ++i)
    			os << obj.a[i] << ", ";
			os << obj.a[obj.numb-1] << ']';
		}
    	return os;
	}
	
	void sort(bool less=true)//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
	{	if (less)
			Qsort_1(a, 0, numb-1);
		else
			Qsort_2(a, 0, numb-1);
	}
    // 若less=true，按照从小到大排列，否则按从大到小排列
	void reverse()//将MyList的元素倒过来。
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

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}




