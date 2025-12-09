#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Goods
{
	string _name;  // 名字
	double _price; // 价格
	int _evaluate; // 评价

	Goods(const char* str, double price, int evaluate)
		:_name(str)
		, _price(price)
		, _evaluate(evaluate)
	{}
};

// 用仿函数来实现【价格升序】
struct ComparePriceLess
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price < gr._price;
	}
};

// 用仿函数来实现【价格降序】
struct CompareEvaluateGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};

// 用仿函数来实现【评价降序】
struct ComparePriceGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._evaluate > gr._evaluate;
	}
};

/*
int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2, 3 }, { "菠萝", 1.5, 4 } };
	
	sort(v.begin(), v.end(), ComparePriceLess());   // 价格升序
	sort(v.begin(), v.end(), ComparePriceGreater()); // 价格降序
	sort(v.begin(), v.end(), ComparePriceGreater()); // 评价降序

	return 0;
}
*/

/*
int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2, 3 }, { "菠萝", 1.5, 4 } };

	// 局部的匿名函数对象
	// [] --> 捕捉列表
	// () --> 参数
	// bool --> 返回值
	// return x < y --> 函数体
	auto less = [](int x, int y)->bool {return x < y; };
	cout << less(1, 2) << endl;

	auto goodsPriceLess = [](const Goods& x, const Goods& y)->bool {return x._price > y._price; }; // 价格降序
	cout << goodsPriceLess(v[0], v[1]) << endl; // 苹果2.1 < 香蕉3

	// 排序的新用法
	sort(v.begin(), v.end(), goodsPriceLess);
	for (const auto& e : v)
	{
		cout << e._name << " : " << e._price << endl; // 降序打印
	}
	cout << "-------------------" << endl;


	// 另外返回值也可以省略
	auto goodsPriceGreater = [](const Goods& x, const Goods& y){return x._price < y._price; };
	sort(v.begin(), v.end(), goodsPriceGreater);
	for (const auto& e : v)
	{
		cout << e._name << " : " << e._price << endl; // 升序打印
	}

	cout << "-------------------" << endl;


	// 简洁用法
	sort(v.begin(), v.end(), [](const Goods& x, const Goods& y) {
		return x._evaluate > y._evaluate;}); // 评价降序
	for (const auto& e : v)
	{
		cout << e._name << " : " << e._evaluate << endl; // 评价降序
	}

	cout << "-------------------" << endl;

	sort(v.begin(), v.end(), [](const Goods& x, const Goods& y) {
		return x._evaluate > y._evaluate; }); // 评价升序
	for (const auto& e : v)
	{
		cout << e._name << " : " << e._evaluate << endl; // 评价升序
	}
	return 0;
}
*/

void func()
{
	cout << "func()" << endl;
}

/*
int main()
{
	int a = 1, b = 2;
	auto add1 = [](int x, int y)->int {return x + y; };
	auto add2 = [](int x, int y){return x + y; }; // lambda一般都不需要写返回值
	
	cout << add1(a, b) << endl;
	cout << add2(a, b) << endl;

	auto swap1 = [](int& x, int& y) {
		int tmp = x;
		x = y;
		y = tmp;
	};
	swap1(a, b);
	cout << a << " : " << b << endl;

	auto swap2 = [](int& x, int& y) {
		int tmp = x;
		x = y;
		y = tmp;

		func(); // 可以调用全局的函数,但是不能调用局部的函数
	};
	swap2(a, b);

	// 捕捉列表
	double rate = 2.5;
	auto add3 = [rate](int x, int y) {return (x + y) * rate; }; // [rate]传值捕捉
	cout << add3(a, b) << endl;
	return 0;
}
*/

/*
int main()
{
	int x = 0, y = 2;
	// 捕捉列表 -- 传值捕捉(是const类型的, 无法修改)
	auto swap1 = [x, y]() {
		int tmp = x;
		x = y;
		y = tmp;
	}; 
	swap1();

	// mutable让捕捉的x和y可以改变，但他们依旧是外面x和y的拷贝
	auto swap1 = [x, y]() mutable{
		int tmp = x;
		x = y;
		y = tmp;
	}; 
	swap1();
	cout << x << " : " << y << endl;

	// 如果想要修改，就采用 引用的方式捕捉

	auto swap2 = [&x, &y]() mutable {
		int tmp = x;
		x = y;
		y = tmp;
	}; 
	swap2();
	cout << x << " : " << y << endl;

	
	int a = 0, b = 1, c = 2, d = 3;
	// 引用捕捉所有对象, 另外()也可以省略
	auto func1 = [&] {
		a++;
		b++;
		c++;
		d++;
	};
	func1();
	cout << a << " : " << b << " : " << c << " : " << d << endl;

	// 引用捕捉所有对象, 除了a
	auto func2 = [&, a] {
		//a++;
		b++;
		c++;
		d++;
	};
	func2();
	cout << a << " : " << b << " : " << c << " : " << d << endl;

	// 捕捉函数
	auto func3 = [&, func1]{
		a++;
		b++;
		c++;
		d++;
		func1();
	};
	func3();
	cout << a << " : " << b << " : " << c << " : " << d << endl;

	return 0;
}
*/

/*
int main()
{
	auto f1 = [](int x, int y) {
		return x + y;
	};
	auto f2 = [](int x, int y) {
		return x + y;
	};

	// f1 = f2; // 会报错, 为什么不能赋值呢？
	// 打印可以看到, 这两个lambda的类型是不一样的, 故无法赋值
	cout << typeid(f1).name() << endl;
	cout << typeid(f2).name() << endl;

	return 0;
}
*/


class Rate
{
public:
	// 构造
	Rate(double rate) : _rate(rate)
	{}

	// 重载operator()
	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};

// 通过调试以后, 转到反汇编可以看出, lambda底层就是仿函数
// 就好比捕捉列表还是相当于 "传参"
int main()
{
	// 函数对象
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);

	// lamber
	auto r2 = [=](double monty, int year)->double {
		return monty * rate * year;
	};
	r2(10000, 2);

	return 0;
}