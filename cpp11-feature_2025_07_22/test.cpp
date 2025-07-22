#include <iostream>
#include <string>
using namespace std;

/*
多态就是函数调用的多种形态，使用多态能够使得不同的对象去完成同一件事时，产生不同的动作和结果。

例如，在现实生活当中，普通人买票是全价，学生买票是半价，而军人允许优先买票。
不同身份的人去买票，所产生的行为是不同的，这就是所谓的多态。

在继承中要想构成多态需要满足两个条件：
- 必须通过基类的指针或者引用调用虚函数。
- 被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写。
*/

// 被virtual修饰的类成员函数被称为虚函数。
// class Person
// {
// public:
// 	//被virtual修饰的类成员函数
// 	virtual void BuyTicket()
// 	{
// 		cout << "买票-全价" << endl;
// 	}
// };
/*
需要注意的是：
- 只有类的非静态成员函数前可以加virtual，普通函数前不能加virtual。
- 虚函数这里的virtual和虚继承中的virtual是同一个关键字，但是它们之间没有任何关系。
  虚函数这里的virtual是为了实现多态，而虚继承的virtual是为了解决菱形继承的数据冗余和二义性。
*/



/*
虚函数的重写也叫做虚函数的覆盖，
若派生类中有一个和基类完全相同的虚函数(返回值类型相同、函数名相同以及参数列表完全相同)，
此时我们称该派生类的虚函数重写了基类的虚函数。
*/

//例如，我们以下Student和Soldier两个子类重写了父类Person的虚函数。
// class Person
// {
// public:
// 	virtual void BuyTicket()
// 	{
// 		cout << "普通人 --> 买票 --> 全价" << endl;
// 	}
// };

//子类
// class Student : public Person
// {
// public:
// 	virtual void BuyTicket()
// 	{
// 		cout << "学生 --> 买票 --> 半价" << endl;
// 	}
// };

//子类
// class Soldier : public Person
// {
// public:
// 	virtual void BuyTicket()
// 	{
// 		cout << "军人 --> 买票 --> 免费" << endl;
// 	}
// };

/*
现在我们就可以通过父类Person的指针或者引用，来调用虚函数BuyTicket，
此时不同类型的对象，调用的就是不同的函数，产生的也是不同的结果，进而实现了函数调用的多种形态。
*/

// void Func(Person& p)
// {
// 	//通过父类的引用调用虚函数
// 	p.BuyTicket();
// }

// void Func(Person* p)
// {
// 	//通过父类的指针调用虚函数
// 	p->BuyTicket();
// }

/*
在重写基类虚函数时，派生类的虚函数不加virtual关键字也可以构成重写，
主要原因是因为继承后基类的虚函数被继承下来了，在派生类中依旧保持虚函数属性。
但是这种写法不是很规范，因此建议在派生类的虚函数前也加上virtual关键字。
*/

// int main()
// {
// 	Person p; // 普通人
// 	Student st; // 学生
// 	Soldier so; // 军人

// 	// 通过父类的引用调用虚函数
// 	Func(p);
// 	Func(st);
// 	Func(so);

// 	cout << endl;

// 	// 通过父类的指针调用虚函数
// 	Func(&p);
// 	Func(&st);
// 	Func(&so);

// 	return 0;
// }


/////////////////////////////////////////////////////////////////////////////////

/*
虚函数重写的两个例外:
- 协变（基类与派生类虚函数的返回值类型不同）
- 析构函数的重写（基类与派生类析构函数的名字不同）
*/

/*
派生类重写基类虚函数时，与基类虚函数返回值类型不同。
即基类虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用，称为协变。
*/

/*
例如，下列代码中基类Person当中的虚函数fun的返回值类型是基类A对象的指针，
派生类Student当中的虚函数fun的返回值类型是派生类B对象的指针，
此时也认为派生类Student的虚函数重写了基类Person的虚函数。
*/

//基类
// class A
// {};

//子类
// class B : public A
// {};

//基类
// class Person
// {
// public:
// 	//返回基类A的指针
// 	virtual A* func()
// 	{
// 		cout << "A* Person::f()" << endl;
// 		return new A;
// 	}
// };

//子类
// class Student : public Person
// {
// public:
// 	//返回子类B的指针
// 	virtual B* func()
// 	{
// 		cout << "B* Student::f()" << endl;
// 		return new B;
// 	}
// };

/*
此时，我们通过父类Person的指针调用虚函数fun，
父类指针若指向的是父类对象，则调用父类的虚函数，
父类指针若指向的是子类对象，则调用子类的虚函数。
*/

// int main()
// {
// 	Person p;
// 	Student st;

// 	//父类指针指向父类对象
// 	Person* ptr1 = &p;
	
// 	//父类指针指向子类对象
// 	Person* ptr2 = &st;

// 	//父类指针ptr1指向的p是父类对象，调用父类的虚函数
// 	ptr1->func();

// 	//父类指针ptr2指向的st是子类对象，调用子类的虚函数
// 	ptr2->func();

// 	return 0;
// }


/*
析构函数的重写（基类与派生类析构函数的名字不同）

如果基类的析构函数为虚函数，此时派生类析构函数只要定义，无论是否加virtual关键字，
都与基类的析构函数构成重写，虽然基类与派生类析构函数名字不同。
*/

//例如，下面代码中父类Person和子类Student的析构函数构成重写。

//父类
// class Person
// {
// public:
// 	virtual ~Person()
// 	{
// 		cout << "~Person()" << endl;
// 	}
// };

//子类
// class Student : public Person
// {
// public:
// 	virtual ~Student()
// 	{
// 		cout << "~Student()" << endl;
// 	}
// };

/*
那父类和子类的析构函数构成重写的意义何在呢？
试想以下场景：分别new一个父类对象和子类对象，并均用父类指针指向它们，
然后分别用delete调用析构函数并释放对象空间。
*/

/*
在这种场景下，若是父类和子类的析构函数没有构成重写就可能会导致内存泄漏，
因为此时delete p1和delete p2都是调用的父类的析构函数，
而我们所期望的是p1调用父类的析构函数，p2调用子类的析构函数，即我们期望的是一种多态行为。

此时只有父类和子类的析构函数构成了重写，
才能使得delete按照我们的预期进行析构函数的调用，才能实现多态。
因此，为了避免出现这种情况，比较建议将父类的析构函数定义为虚函数。
*/

// int main()
// {
// 	//分别new一个父类对象和子类对象，并均用父类指针指向它们
// 	Person* p1 = new Person;
// 	Person* p2 = new Student;

// 	//使用delete调用析构函数并释放对象空间
// 	delete p1;
// 	cout << endl;
// 	delete p2;
// 	return 0;
// }



////////////////////////////////////////////////////////////////////////////////////////////////


/*
从上面可以看出，C++对函数重写的要求比较严格，
有些情况下由于疏忽可能会导致函数名的字母次序写反而无法构成重写，而这种错误在编译期间是不会报错的，
直到在程序运行时没有得到预期结果再来进行调试会得不偿失，
因此，C++11提供了final和override两个关键字，可以帮助用户检测是否重写。
*/

//final：修饰虚函数，表示该虚函数不能再被重写。

/*
例如，父类Person的虚函数BuyTicket被final修饰后就不能再被重写了，子类若是重写了父类的BuyTicket函数则编译报错。
*/

/*
//父类
class Person
{
public:
	//被final修饰，该虚函数不能再被重写
	virtual void BuyTicket() final
	{
		cout << "买票-全价" << endl;
	}
};

//子类
class Student : public Person
{
public:
	//重写，编译报错
	virtual void BuyTicket()
	{
		cout << "买票-半价" << endl;
	}
};

//子类
class Soldier : public Person
{
public:
	//重写，编译报错
	virtual void BuyTicket()
	{
		cout << "优先-买票" << endl;
	}
};
*/


//override：检查派生类虚函数是否重写了基类的某个虚函数，如果没有重写则编译报错。

/*
例如，子类Student和Soldier的虚函数BuyTicket被override修饰，
编译时就会检查子类的这两个BuyTicket函数是否重写了父类的虚函数，如果没有则会编译报错。
*/

/*
//父类
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "买票-全价" << endl;
	}
};

//子类
class Student : public Person
{
public:
	//子类完成了父类虚函数的重写，编译通过
	virtual void BuyTicket() override
	{
		cout << "买票-半价" << endl;
	}
};

//子类
class Soldier : public Person
{
public:
	//子类没有完成了父类虚函数的重写，编译报错
	virtual void BuyTicket(int i) override
	{
		cout << "优先-买票" << endl;
	}
};
*/