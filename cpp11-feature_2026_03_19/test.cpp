#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

namespace edison
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

		// 构造函数
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(const char* str) -- 构造" << endl;

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
			cout << "string(const string& s) -- 拷贝构造（深拷贝）" << endl;

			//string tmp(s._str);
			//swap(tmp);
		}

		// ===== 新增：移动构造函数 =====
		// 接收右值引用（&&），转移资源而非拷贝
		string(string&& s) noexcept
			: _str(nullptr), _size(0), _capacity(0)
		{
			cout << "string(string&& s) -- 移动构造（无拷贝）" << endl;
			swap(s);  // 将 s 的资源全部窃取过来
		}

		// 赋值重载
		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 赋值重载（深拷贝）" << endl;
			string tmp(s);
			swap(tmp);

			return *this;
		}

		// ===== 新增：移动赋值运算符 =====
		// 接收右值引用，实现资源转移
		string& operator=(string&& s) noexcept
		{
			cout << "string& operator=(string&& s) -- 移动赋值（无拷贝）" << endl;

			if (this != &s) // 防止自赋值
			{
				swap(s); // 交换资源：当前对象接管s的_str，s接管当前对象的旧资源（析构时释放）
			}
			return *this;
		}

		// 析构函数
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


//class Person
//{
//public:
//	Person(const char* name = "", int age = 0)
//		:_name(name)
//		, _age(age)
//	{}
//
//	// 拷贝构造
//	Person(const Person& p)
//		:_name(p._name)
//		,_age(p._age)
//	{}
//
//	// 赋值重载
//	Person& operator=(const Person& p)
//	{
//		if(this != &p)
//		{
//			_name = p._name;
//			_age = p._age;
//		}
//		return *this;
//	}
//
//	// 移动赋值
//	Person& operator=(Person&& p)
//	{
//		if (this != &p)
//		{
//			_name = std::move(p._name);
//			_age = p._age;
//		}
//		return *this;
//	}
//
//	Person(Person&& p) = default; // 强制生成【移动构造】函数
//
//	~Person()
//	{}
//private:
//	edison::string _name;
//	int _age;
//};
//
//
//int main()
//{
//	Person s1;
//	cout << endl;
//	
//	Person s2 = s1;
//	cout << endl;
//
//	Person s3 = std::move(s1);
//	cout << endl;
//
//	Person s4;
//	cout << endl;
//
//	s4 = std::move(s2);
//
//	return 0;
//}




//class Base
//{
//public:
//	virtual void func(int x) {}
//};
//
//class Derived : public Base
//{
//public:
//	void func(double x) {}  // 你以为你重写了，其实没有
//};
//
//
//int main()
//{
//	;
//	return 0;
//}

/////////////////////////////////////////////////////////////////////////////////////



template<class F, class T>
T useF(F f, T x)
{
	static int count = 0;
	cout << "count:" << ++count << endl;
	cout << "count:" << &count << endl;

	return f(x);
}


double f(double i)
{
	return i / 2;
}

struct Functor
{
	double operator()(double d)
	{
		return d / 3;
	}
};




//int main()
//{
//	// 函数指针
//	cout << useF(f, 11.11) << endl;
//	cout << endl;
//
//	// 函数对象
//	cout << useF(Functor(), 11.11) << endl;
//	cout << endl;
//
//	// lambda表达式
//	cout << useF([](double d)->double { return d / 4; }, 11.11) << endl;
//
//	return 0;
//}



// 包装器头文件
#include <functional>


//int main()
//{
//	// 函数名
//	std::function<double(double)> func1 = f;
//	cout << useF(func1, 11.11) << endl;
//	cout << endl;
//
//	// 函数对象
//	std::function<double(double)> func2 = Functor();
//	cout << useF(func2, 11.11) << endl;
//	cout << endl;
//
//	// lamber表达式
//	std::function<double(double)> func3 = [](double d)->double { return d / 4; };
//	cout << useF(func3, 11.11) << endl;
//	cout << endl;
//
//	return 0;
//}






#include <vector>

//int main()
//{
//	// 包装器 --> 解决可调用对象的类型问题
//	function<double(double)> f1 = f;
//	function<double(double)> f2 = [](double d)->double { return d / 4; };
//	function<double(double)> f3 = Functor();
//	
//	// 初始化
//	vector<function<double(double)>> v = { f1, f2, f3 };
//	double n = 3.3;
//	for (auto f : v)
//	{
//		cout << f(n++) << endl;
//	}
//
//	return 0;
//}




//int Sub(int a, int b)
//{
//	return a - b;
//}
//
//int main()
//{
//	// 表示绑定函数 Sub 参数分别由调用 rSub 的第一、二个参数指定
//	function<int(int, int)> rSub1 = std::bind(Sub, placeholders::_1, placeholders::_2);
//	cout << rSub1(10, 5) << endl; // 10 - 5
//	
//	// 参数调换顺序
//	function<int(int, int)> rSub2 = std::bind(Sub, placeholders::_2, placeholders::_1);
//	cout << rSub2(10, 5) << endl; // 5 - 10
//
//
//	return 0;
//}








//double Plus(int a, int b, double rate)
//{
//	return (a + b) * rate;
//}
//
//
//double PPlus(double rate, int a, int b)
//{
//	return rate * (a + b);
//}
//
//
//int main()
//{
//	function<double(int, int)> PPlus1 = bind(PPlus, 5.0, placeholders::_1, placeholders::_2);
//	cout << PPlus1(5, 3) << endl;
//
//	function<double(int, int)> PPlus2 = bind(PPlus, 5.2, placeholders::_1, placeholders::_2);
//	cout << PPlus2(5, 3) << endl;
//
//	function<double(int, int)> PPlus3 = bind(PPlus, 5.4, placeholders::_1, placeholders::_2);
//	cout << PPlus3(5, 3) << endl;
//
//	return 0;
//}



//class SubType
//{
//public:
//	// 静态成员函数
//	static int sub(int a, int b)
//	{
//		return a - b;
//	}
//
//	// 普通成员函数
//	int ssub(int a, int b, int rate)
//	{
//		return (a - b) * rate;
//	}
//};
//
//
//
//int main()
//{
//	function<int(int, int)> Sub1 = bind(SubType::sub, placeholders::_1, placeholders::_2);
//	cout << Sub1(5, 3) << endl;
//
//	// 非静态的成员函数在进行绑定的时候，需要加一个 &(取地址) 符号
//	// 并且还要重新定义一个 st 对象，然后对 st 对象进行取地址绑定
//	SubType st;
//	function<int(int, int)> Sub2 = bind(&SubType::ssub, &st, placeholders::_1, placeholders::_2, 5);
//	cout << Sub2(5, 3) << endl;
//
//	// 当然，也可以不传 st 对象地址，而且直接传递一个 SubType 对象
//	function<int(int, int)> Sub3 = bind(&SubType::ssub, SubType(), placeholders::_1, placeholders::_2, 5);
//	cout << Sub3(5, 3) << endl;
//
//	return 0;
//}



int Sub(int a, int b)
{
	return a - b;
}

int main()
{
	// 表示绑定函数 Sub 参数分别由调用 rSub1 的第一、二个参数指定
	function<int(int, int)> rSub1 = bind(Sub, placeholders::_1, placeholders::_2);
	cout << rSub1(10, 5) << endl; // 10 - 5

	// rSub2 的类型为 function<int(int, int, int)> 与 rSub1 类型一样
	// 表示绑定函数 Sub 的第一，二为： 10， 5
	auto rSub2 = bind(Sub, 10, 5);
	cout << rSub2() << endl;
	
	// 参数调换顺序
	auto rSub3 = std::bind(Sub, placeholders::_2, placeholders::_1);
	cout << rSub3(10, 5) << endl; // 5 - 10

	return 0;
}