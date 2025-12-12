#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <list>
#include <string>

using namespace std;



// 模板可变参数（了解即可）
/*
template <class T, class ...Args>
void ShowList(T value, Args... args)
{
	cout << sizeof...(args) << endl; // 查看参数包的个数
}

int main()
{
	ShowList(1); // 1传给value, 参数包有0个
	ShowList(1, 2); // 1传给value, 2传给参数包
	ShowList(1, 2, 3.3); // 1传给value, 2 和 3.3 传给参数包

	return 0;
}*/

/////////////////////////////////////////////

// 如何取出参数包的内容呢？
// 没错，下面就是一种方法，叫做：编译递归，通过第一个参数不断的去推导参数包的值
/*
template <class T>
void ShowList(T value)
{
	// 结束条件的函数
	cout << value << " ";
	cout << endl;
}

template <class T, class ...Args>
void ShowList(T value, Args... args)
{
	cout << value << " ";
	ShowList(args...);
}

int main()
{
	ShowList(1); 
	ShowList(1, 2); 
	ShowList(1, 2, 3.3); 

	return 0;
}*/



///////////////////////////////////////////////////////////////////////
// 实现一个C++类型的printf
/*
void _ShowList()
{
	// 结束条件的函数
	cout << endl;
}

template <class T, class ...Args>
void _ShowList(T value, Args... args)
{
	cout << value << " ";
	_ShowList(args...);
}

// args代表 0-N 的参数包
template <class ...Args>
void cppPrint(Args... args)
{
	_ShowList(args...);
}


int main()
{
	cppPrint();
	cppPrint(1);
	cppPrint(1, 2);
	cppPrint(1, 2, 3.3);

	return 0;
}
*/


///////////////////////////////////////////////////////////////////////
// 逗号表达式展开参数包

/*
// 重载（为了打印0个参数）
void cppPrint()
{
	cout << endl;
}

template <class T>
void PrintArg(T t)
{
	cout << t << " ";
}

//展开函数
template <class ...Args>
void cppPrint(Args... args)
{
	int arr[] = { (PrintArg(args), 0)... };
	cout << endl;
}

int main()
{
	cppPrint();
	cppPrint(1);
	cppPrint(1, 2);
	cppPrint(1, 2, 3.3);
	cppPrint(1, 2, 3.3, string("hello world"));

	return 0;
}
*/

///////////////////////////////////////////////////////////////////////
// 不使用逗号表达式，展开参数包

/*
// 重载（为了打印0个参数）
void cppPrint()
{
	cout << endl;
}

template <class T>
int PrintArg(T t)
{
	cout << t << " ";

	return 0;
}

//展开函数
template <class ...Args>
void cppPrint(Args... args)
{
	int arr[] = { PrintArg(args)... }; // 参数包有几个值, 就要调几次这个PrintArg函数
	cout << endl;
}

int main()
{
	cppPrint();
	cppPrint(1);
	cppPrint(1, 2);
	cppPrint(1, 2, 3.3);
	cppPrint(1, 2, 3.3, string("hello world"));

	return 0;
}*/



/////////////////////////////////////////////////////////////////

/*
class Date
{
public:
	Date(int y = 1, int m = 1, int d = 1)
		: _year(y), _month(m), _day(d)
	{}

	// 拷贝构造函数
	Date(const Date& other)
		: _year(other._year), _month(other._month), _day(other._day)
	{}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

template <class ...Args>
Date* Create(Args... args)
{
	Date* ret = new Date(args...);
	return ret;
}

int main()
{
	// 参数包是3个参数, 而Date类的构造函数的参数也是3个, 刚好匹配上了
	Date* p1 = Create();
	Date* p2 = Create(2025);
	Date* p3 = Create(2025, 12);
	Date* p4 = Create(2025, 12, 12);

	p1->Print();
	p2->Print();
	p3->Print();
	p4->Print();

	Date d(2026, 1, 1);
	Date* p5 = Create(d); // p5是去调用拷贝构造, 我们没有写, 那么编译器会默认生成
	p5->Print();

	return 0;
}*/



//////////////////////////////////////////////////////////////////
//那么相对insert和emplace系列接口的优势到底在哪里呢？

// emplace_back --> 模板的可变参数
/*
int main()
{
	std::list< std::pair<int, char> > mylist;

	mylist.emplace_back(10, 'a');
	mylist.emplace_back(20, 'b');
	mylist.emplace_back(make_pair(30, 'c'));

	mylist.push_back(make_pair(40, 'd'));
	mylist.push_back({ 50, 'e' });

	for (auto e : mylist)
		cout << e.first << ":" << e.second << endl;

	return 0;
}*/


// 下面我们试一下带有拷贝构造和移动构造的std::string，再试试呢
// 我们会发现其实差别也不到，emplace_back是直接构造了，
// push_back是先构造，再移动构造，其实也还好。
#include <cassert>

namespace edc
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(const char* str)" << endl;

			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// s1.swap(s2)
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}

		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 深拷贝" << endl;

			//string tmp(s._str);
			//swap(tmp);
		}

		string(string&& s)
			:_str(nullptr)
		{
			cout << "string(string&& s) -- 移动拷贝" << endl;

			swap(s);
		}

		// 赋值重载
		string& operator=(const string& s)
		{
			cout << "string& operator=(string s) -- 深拷贝" << endl;
			string tmp(s);
			swap(tmp);

			return *this;
		}

		string& operator=(string&& s)
		{
			cout << "string& operator=(string && s) -- 移动拷贝" << endl;
			swap(s);

			return *this;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;

				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		//string operator+=(char ch)
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		const char* c_str() const
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity; // 不包含最后做标识的\0
	};
}

/*
int main()
{
	std::list< std::pair<int, edc::string> > mylist;

	//mylist.emplace_back(10, "sort");
	//mylist.emplace_back(make_pair(20, "sort"));

	mylist.push_back(make_pair(30, "sort"));
	cout << "-----------------------" << endl;
	mylist.push_back({ 40, "sort" });

	return 0;
}*/


//////////////////////////////////////
// push_back是先构造，再拷贝构造, 会创建两次对象
// emplace_back是直接构造了，

class Date
{
public:
	Date(int y = 1, int m = 1, int d = 1)
		: _year(y), _month(m), _day(d)
	{
		cout << "Date()构造" << endl;
	}

	Date(const Date& d)
		: _year(d._year), _month(d._month), _day(d._day)
	{
		cout << "Date()拷贝构造" << endl;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

/*
int main()
{
	std::list<Date> lt;
	
	Date d(2025, 12, 12);

	cout << "--------------------------" << endl;
	
	//lt.push_back(d); // push_back只能传日期类对象

	// 把参数包一路往下传, 直接去构造或者拷贝构造结点中的日期类对象
	lt.emplace_back(d); // 可以传日期类对象

	cout << "--------------------------" << endl;

	lt.emplace_back(2026, 11, 11); // 也可以传日期类对象的参数包

	return 0;
}*/


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 类的新功能 
/*
原来C++类中，有6个默认成员函数
C++11 新增了两个：移动构造函数和移动赋值运算符重载。

这两个函数分为两种情况：
1.深拷贝的类需要自己实现；
  2.浅拷贝的类, 不需要实现; 

两个疑问：
1. 我们不写，自动生成的会干什么事情呢？
2. 我们不写，什么情况下会自动生成呢？
*/
 

class Person
{
public:
	Person(const char* name = "", int age = 0)
		:_name(name)
		, _age(age)
	{}

private:
	edc::string _name; // edc::string是我自己实现的一个string类
	int _age;
};

int main()
{
	Person s1; //拷贝构造
	Person s2 = s1; //拷贝构造

	//Person s3 = std::move(s1);
	//Person s4;
	//s4 = std::move(s2);
	return 0;
}


/*
如果要实现析构函数，那么就需要写拷贝构造和赋值
因为自己实现析构, 那么通常意味着这个类是会进行深拷贝的类
*/