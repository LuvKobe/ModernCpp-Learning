#include <iostream>
#include <string>
using namespace std;

//继承呈现了面向对象程序设计的层次结构，体现了由简单到复杂的认知过程。继承便是类设计层次的复用.

//以下代码中Student类和Teacher类就继承了Person类。
//继承后，父类Person的成员，包括成员函数和成员变量，都会变成子类的一部分，
//也就是说，子类Student和Teacher复用了父类Person的成员。
// class Person
// {
// public:
//     void Print()
//     {
//         cout << "name: " << _name << endl;
//         cout << "age: " << _age << endl;
//     }
// protected:
//     string _name = "张三";
//     int _age = 18;
// };

// // 子类
// class Student : public Person
// {
// public:
//     Student()
//         : _stuid(001)
//     {}
//     void Print()
//     {
//         cout << "name: " << _name << endl;
//         cout << "age: " << _age << endl;
//         cout << "stuid: " << _stuid << endl;
//     }
// protected:
//     int _stuid; // 学号
// };

// // 子类
// class Teacher : public Person
// {
// public:
//     Teacher()
//         : _jobid(002)
//     {}
//     void Print()
//     {
//         cout << "name: " << _name << endl;
//         cout << "age: " << _age << endl;
//         cout << "jobid: " << _jobid << endl;
//     }
// protected:
//     int _jobid; // 工号
// };


// int main()
// {
//     Person p1;
//     //p1.Print();

//     Student s1;
//     s1.Print();

//     Teacher t1;
//     t1.Print();

//     return 0;
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
在继承当中，父类也称为基类，子类是由基类派生而来的，所以子类又称为派生类。
三种访问限定符的权限大小为：public > protected > private

访问限定符有以下三种：public > protected > private

继承的方式也有类似的三种：public继承, protected继承, private继承

基类的private成员无论以什么方式继承，在派生类中都是不可见的。

这里的不可见是指基类的私有成员虽然被继承到了派生类对象中，但是语法上限制派生类对象不管在类里面还是类外面都不能去访问它。

基类的private成员在派生类中是不能被访问的，如果基类成员不想在类外直接被访问，但需要在派生类中能访问，
就需要定义为protected，由此可以看出，protected限定符是因继承才出现的。
*/


//在使用继承的时候也可以不指定继承方式，使用关键字class时默认的继承方式是private，使用struct时默认的继承方式是public。
//在关键字为class的派生类当中，所继承的基类成员_name的访问方式变为private。

// //基类
// class Person
// {
// public:
// 	string _name = "张三"; //姓名
// };

// //派生类
// class Student : Person //默认为private继承
// {
// protected:
// 	int _stuid;   //学号
// };


//而在关键字为struct的派生类当中，所继承的基类成员_name的访问方式仍为public。
//虽然继承时可以不指定继承方式而采用默认的继承方式，但还是最好显示的写出继承方式。

// //基类
// class Person
// {
// public:
// 	string _name = "张三"; //姓名
// };

// //派生类
// struct Student : Person //默认为public继承
// {
// protected:
// 	int _stuid;   //学号
// };

//派生类对象可以赋值给基类的对象、基类的指针以及基类的引用，因为在这个过程中，会发生基类和派生类对象之间的赋值转换。
// class Person
// {
// public:
//     string _name;
//     string _sex;
//     int _age;
// };

// class Student : public Person
// {
// protected:
//     int _stuid;
// };

// int main()
// {
//     Student s;

//     Person p = s; //派生类对象赋值给基类对象

//     Person* ptr = &s; //派生类对象赋值给基类指针

//     Person& ref = s;  //派生类对象赋值给基类引用
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
在继承体系中的基类和派生类都有独立的作用域。
若子类和父类中有同名成员，子类成员将屏蔽父类对同名成员的直接访问，这种情况叫隐藏，也叫重定义。
*/

//对于以下代码，访问成员_num时将访问到子类当中的_num。

//父类
// class Person
// {
// protected:
// 	int _num = 111;
// };

// //子类
// class Student : public Person
// {
// public:
// 	void fun()
// 	{
// 		//cout << _num << endl;
//         //若此时我们就是要访问父类当中的_num成员，我们可以使用作用域限定符进行指定访问。
//         cout << Person::_num << endl; //指定访问父类当中的_num成员
// 	}
// protected:
// 	int _num = 999;
// };

// int main()
// {
// 	Student s;
// 	s.fun(); //999

// 	return 0;
// }


// //父类
// class Person
// {
// public:
// 	void fun(int x)
// 	{
// 		cout << x << endl;
// 	}
// };

// //子类
// class Student : public Person
// {
// public:
// 	void fun(double x)
// 	{
// 		cout << x << endl;
// 	}
// };

// int main()
// {
// 	Student s;
// 	s.fun(3.14);       //直接调用子类当中的成员函数fun

// 	s.Person::fun(20); //指定调用父类当中的成员函数fun
// 	return 0;
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//默认成员函数，即我们不写编译器会自动生成的函数，类当中的默认成员函数有以下六个：
//构造函数&&析构函数、拷贝构造&&赋值重载、取地址重载(很少用到)

// 父类
// class Person
// {
// public:
//     // 构造函数
//     Person(const string& name = "edison")
//         :_name(name)
//     {
//         cout << "调用构造函数Person()" << endl;
//     }

//     // 拷贝构造函数
//     Person(const Person& p)
//         :_name(p._name)
//     {
//         cout << "调用拷贝构造函数Person(const Person& p)" << endl;
//     }

//     //赋值运算符重载函数
//     Person& operator=(const Person& p)
//     {
//         cout << "调用赋值运算符重载函数operator=(const Person& p)" << endl;
//         /*
//         如果 this == &p，说明你执行了 a = a，也就是自赋值，这时不需要做任何操作，否则可能会引发错误或浪费资源。
//         Person a;
//         a = a; // 会触发自赋值
//         */
//         if (this != &p)    // &p 是传入对象的地址。
//         {
//             // 执行实际的赋值，将传入对象 p 的 _name 成员赋值给当前对象的 _name。
//             // 因为 _name 是 string 类型，它的赋值操作会调用 string 类的 operator=，深拷贝内容。
//             _name = p._name;
//         }
//         return *this;
//     }

//     // 析构函数
//     ~Person()
//     {
//         cout << "调用析构函数~Person()" << endl;
//     }
// private:
//     string _name;
// };

/*
“this 指针” 是 C++ 中一个非常重要的概念，它是每个非静态成员函数 隐式拥有 的一个指针，指向调用该成员函数的 当前对象 本身。

Person a("edison");
a.operator=(b); // 相当于 a = b;

在 operator= 函数中：
- this 就是 &a，指向对象 a 的地址。
- p 是 b 的引用，代表右侧赋值的对象。

所以 this != &p 就是：“我自己不是要赋值的对象”，防止自赋值。
*/

// 测试父类
// void test1()
// {
//     Person a("edison"); // 调用构造函数
//     Person b(a); // 调用拷贝构造函数

//     cout << endl;

//     Person c;
//     c.operator=(b); // 调用赋值运算符重载函数
// }

/*
测试结果如下：
[edison@vm-centos:~/myCode/Cpp11]$ ./myproc 
调用构造函数Person()
调用拷贝构造函数Person(const Person& p)

调用构造函数Person()
调用赋值运算符重载函数operator=(const Person& p)
调用析构函数~Person()
调用析构函数~Person()
调用析构函数~Person()
*/


//我们用该基类派生出Student子类，Student类当中的默认成员函数的基本逻辑如下：
// class Student : public Person
// {
// public:
//     // 构造函数
//     Student(const string& name, int id)
//         :Person(name) //调用父类的构造函数初始化父类的那一部分成员
//         , _stuId(id) //初始化子类的成员
//     {
//         cout << "调用构造函数Student()" << endl;
//     }

//     // 拷贝构造函数
//     Student(const Student& s)
//         :Person(s) //调用父类的拷贝构造函数完成父类成员的拷贝构造
//         , _stuId(s._stuId) //拷贝构造派生类的成员
//     {
//         cout << "调用拷贝构造函数Student(const Student& s)" << endl;
//     }

//     // 赋值运算符重载函数
//     Student& operator=(const Student& s)
//     {
//         cout << "调用赋值运算符重载函数operator=(const Student& p)" << endl;
//         if (this != &s)
//         {
//             Person::operator=(s); //调用父类的operator=完成基类成员的赋值
//             _stuId = s._stuId; //完成子类成员的赋值
//         }
//         return *this;
//     }

//     // 析构函数
//     ~Student()
//     {
//         cout << "调用析构函数~Student()" << endl;
//         // 子类的析构函数会在被调用完成后自动调用父类的析构函数
//     }
// private:
//     int _stuId;
// };

// 测试子类
// void test2()
// {
//     Student s1("张三", 001); // 调用构造函数
//     cout << endl;

//     Student s2(s1); // 调用拷贝构造函数
//     cout << endl;

//     Student s3("李四", 002); // 调用构造函数
//     cout << endl;

//     s3.operator=(s1); // 调用赋值运算符重载函数
//     cout << endl;
// }

/*
运行结果如下：
[edison@vm-centos:~/myCode/Cpp11]$ ./myproc 
调用构造函数Person()
调用构造函数Student()

调用拷贝构造函数Person(const Person& p)
调用拷贝构造函数Student(const Student& s)

调用构造函数Person()
调用构造函数Student()

调用赋值运算符重载函数operator=(const Student& p)
调用赋值运算符重载函数operator=(const Person& p)

调用析构函数~Student()
调用析构函数~Person()
调用析构函数~Student()
调用析构函数~Person()
调用析构函数~Student()
调用析构函数~Person()

*/

// int main()
// {
//     test2();
//     return 0;
// }

/*
总结：
1、子类的构造函数被调用时，会自动调用父类的构造函数初始化父类的那一部分成员，
   如果父类当中没有默认的构造函数，则必须在子类构造函数的初始化列表当中显示调用父类的构造函数。

2、子类的拷贝构造函数必须调用父类的拷贝构造函数，完成父类成员的拷贝构造。

3、子类的赋值运算符重载函数必须调用父类的赋值运算符重载函数，完成父类成员的赋值。

4、子类的析构函数会在被调用完成后自动调用父类的析构函数，清理父类成员。

5、子类对象初始化时，会先调用父类的构造函数，再调用子类的构造函数。

6、子类对象在析构时，会先调用子类的析构函数，再调用父类的析构函数。

说明一下;
1、父类的构造函数、拷贝构造函数、赋值运算符重载函数我们都可以在子类当中自行进行调用，
   而父类的析构函数是当子类的析构函数被调用后由编译器自动调用的，我们若是自行调用父类的构造函数就会导致父类被析构多次的问题。

2、我们知道，创建子类对象时，是先创建的父类成员再创建的子类成员，
  编译器为了保证析构时，先析构子类成员再析构父类成员的顺序析构，
  所以编译器会在子类的析构函数被调用后，自动调用父类的析构函数。
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//友元关系不能继承，也就是说基类的友元可以访问基类的私有和保护成员，但是不能访问派生类的私有和保护成员。
// 父类
// class Student;
// class Person
// {
// public:
// 	//声明Display是Person的友元
// 	friend void Display(const Person& p, const Student& s);
// protected:
// 	string _name; //姓名
// };

// // 子类
// class Student : public Person
// {
// public: 
//     //声明Display是Student的友元
// 	friend void Display(const Person& p, const Student& s);
// protected:
// 	int _id; //学号
// };

//若想让Display函数也能够访问派生类Student的私有和保护成员，只能在派生类Student当中进行友元声明。
// void Display(const Person& p, const Student& s)
// {
// 	cout << p._name << endl; //可以访问
// 	cout << s._id << endl;  //无法访问
// }

// int main()
// {
// 	Person p;
// 	Student s;
    
// 	Display(p, s);
// 	return 0;
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//父类
// class Person
// {
// public:
// 	Person() 
// 	{ 
// 		_count++; 
//         cout << "调用构造函数Person()" << endl;
// 	}
// 	Person(const Person& p) 
// 	{
// 		_count++;
//         cout << "调用拷贝构造函数Person(const Person& p)" << endl;
// 	}
// protected:
// 	string _name; //姓名
// public:
// 	static int _count; //统计人的个数。
// };
// int Person::_count = 0; //静态成员变量在类外进行初始化

// //子类
// class Student : public Person
// {
// protected:
// 	int _stuNum; //学号
// };

// //子类
// class Graduate : public Person
// {
// public:
//     // 构造函数
//     Graduate()
//     {
//         cout << "调用构造函数Graduate()" << endl;
//     }
// protected:
// 	string _seminarCourse; //研究科目
// };

// int main()
// {
//     Student s1;
//     Student s2(s1);
//     cout << Person::_count << endl;
//     cout << Student::_count << endl;
//     cout << endl;
//     Student s3;
//     Graduate s4;
//     cout << Person::_count << endl;
//     cout << Student::_count << endl;
//     return 0;
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
继承的方式：

- 单继承：一个子类只有一个直接父类时称这个继承关系为单继承。

- 多继承：一个子类有两个或两个以上直接父类时称这个继承关系为多继承。

- 菱形继承：菱形继承是多继承的一种特殊情况。
*/

/*
// 单继承
//父类
class Person
{
protected:
    string _name; //姓名
};

//子类1
class Student : public Person
{
protected:
    int _stuId; // 学号
};

//子类2
class Graduate : public Student
{
protected:
    string _course; //研究科目
};
*/

//-----------------------------------------------------------------------------

/*
// 多继承
//父类1
class Student
{
protected:
    int _stuId; // 学号
};

//父类2
class Teacher
{
protected:
    int _techId; // 工号
};

//子类
class Assistant : public Student, public Teacher
{
public:
    string _name;
};
*/

//-----------------------------------------------------------------------------

//菱形继承的继承方式存在数据冗余和二义性的问题。
// 父类
// class Person
// {
// public:
// 	string _name; //姓名
// };

// // 子类1
// class Student : public Person
// {
// protected:
// 	int _num; //学号
// };

// // 子类2
// class Teacher : public Person
// {
// protected:
// 	int _id; //职工编号
// };

// //孙子类
// class Assistant : public Student, public Teacher
// {
// protected:
// 	string _majorCourse; //主修课程
// };


/*
Assistant 从两个基类 Student 和 Teacher 同时继承，而它们都继承自 Person，
这会导致 “二义性继承”（diamond problem）
Assistant 拥有两份 Person::_name 成员，编译器不知道你是指哪个。

因为：
   Assistant
  ↙       ↘
Student  Teacher
   ↘       ↙
    Person (x2!)

Assistant 通过 Student 和 Teacher 各自继承了一份 Person，即：
a.Student::_name
a.Teacher::_name
所以 a._name 不明确。
*/

// int main()
// {
// 	Assistant a;
// 	//a._name = "peter"; //二义性：无法明确知道要访问哪一个_name
// 	return 0;
// }

//-----------------------------------------------------------------------------

//为了解决菱形继承的二义性和数据冗余问题，出现了虚拟继承。

// 父类
class Person
{
public:
	string _name; // 姓名
};

// 子类1
class Student : virtual public Person
{
protected:
	int _num; // 学号
};

// 子类2
class Teacher : virtual public Person
{
protected:
	int _id; // 职工编号
};

// 孙子类
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};

int main()
{
	Assistant a;
	a._name = "edison"; // ✅ 不再模糊

    //cout << a.Student::_name << endl; //peter
    //cout << a.Teacher::_name << endl; //peter
    
    //cout << &a.Student::_name << endl; 
    //cout << &a.Teacher::_name << endl; 

    //你已经虚继承了，直接写 a._name 就是最简洁和清晰的方式。
    cout << a._name << endl;
    cout << &a._name << endl; // ✅ 也是唯一一份地址

    //如果你想验证地址相同，也可以这样写更清晰：
    cout << "Address via Student: " << static_cast<void*>(&a.Student::_name) << endl;
    cout << "Address via Teacher: " << static_cast<void*>(&a.Teacher::_name) << endl;


	return 0;
}

/*
虚继承解决了什么？
让 Student 和 Teacher 共享 同一份 Person 数据（而不是各自复制一份）。
避免二义性，Assistant 中只有一个 _name。

小贴士:
- 多重继承时，只要多个路径会继承同一个基类（即“菱形继承”结构），你必须用虚继承。
- 如果你不打算用虚继承，那访问时要写清楚是哪条路径的成员，例如 a.Student::_name（但不推荐这样做）。


⚠️ 面main函数中你应该避免这样访问的几个原因：
❌ 1. a.Student::_name 只是绕远路
你已经虚继承了，直接写 a._name 就是最简洁和清晰的方式。

❌ 2. 暴露实现细节
如果将来你不再虚继承或修改继承层级，这种路径式访问会使代码失效或变得模糊。

❌ 3. 会误导维护者
虽然地址相同，但其他人看到这代码会以为你在访问不同的成员（因为路径不同），这会造成理解障碍。
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
多人都说C++语法复杂，其实多继承就是一个体现。
有了多继承，就可能存在菱形继承，有了菱形继承就有菱形虚拟继承，底层实现就很复杂。
所以一般不建议设计出菱形继承，否则代码在复杂度及性能上都容易出现问题，当菱形继承出问题时难以分析，并且会有一定的效率影响。

继承是一种is-a的关系，也就是说每个派生类对象都是一个基类对象；

而组合是一种has-a的关系，若是B组合了A，那么每个B对象中都有一个A对象。
*/

//例如，车类和宝马类就是is-a的关系，它们之间适合使用继承。
class Car
{
protected:
	string _colour; //颜色
	string _num; //车牌号
};

class BMW : public Car
{
public:
	void Drive()
	{
		cout << "this is BMW" << endl;
	}
};

//而车和轮胎之间就是has-a的关系，它们之间则适合使用组合。
class Tire
{
protected:
	string _brand; //品牌
	size_t _size; //尺寸
};

class Car1
{
protected:
	string _colour; //颜色
	string _num; //车牌号
	Tire _t; //轮胎
};

//若是两个类之间既可以看作is-a的关系，又可以看作has-a的关系，则优先使用组合。
//原因如下：
/*
1、继承允许你根据父类的实现来定义子类的实现，这种通过生成子类的复用通常被称为白箱复用(White-boxreuse)。
术语“白箱”是相对可视性而言：
- 在继承方式中，父类的内部细节对于子类可见，继承一定程度破坏了父类的封装，父类的改变对派生类有很大的影响，
  子类和父类间的依赖性关系很强，耦合度高。

2、组合是类继承之外的另一种复用选择，新的更复杂的功能可以通过组装或组合对象来获得。
对象组合要求被组合的对象具有良好定义的接口，这种复用风格被称之为黑箱复用(Black-box reuse)，
因为对象的内部细节是不可见的，对象只以“黑箱”的形式出现，
组合类之间没有很强的依赖关系，耦合度低，优先使用对象组合有助于你保持每个类被封装。

3、实际中尽量多使用组合，组合的耦合度低，代码维护性好。
不过继承也是有用武之地的，有些关系就适合用继承，另外要实现多态也必须要继承。
若是类之间的关系既可以用继承，又可以用组合，则优先使用组合。
*/

//相关笔试面试题
/*
1、什么是菱形继承？菱形继承的问题是什么？
- 菱形继承是多继承的一种特殊情况，两个子类继承同一个父类，而又有子类同时继承这两个子类，我们称这种继承为菱形继承。
- 菱形继承因为子类对象当中会有两份父类的成员，因此会导致数据冗余和二义性的问题。
- 二义性：无法明确知道要访问哪一个成员。

2、什么是菱形虚拟继承？如何解决数据冗余和二义性？
- 菱形虚拟继承是指在菱形继承的腰部使用虚拟继承(virtual)的继承方式，
菱形虚拟继承对于D类对象当中重复的A类成员只存储一份，
然后采用虚基表指针和虚基表使得D类对象当中继承的B类和C类可以找到自己继承的A类成员，从而解决了数据冗余和二义性的问题。

3、继承和组合的区别？什么时候用继承？什么时候用组合？
- 继承是一种is-a的关系，而组合是一种has-a的关系。
如果两个类之间是is-a的关系，使用继承；
如果两个类之间是has-a的关系，则使用组合；
如果两个类之间的关系既可以看作is-a的关系，又可以看作has-a的关系，则优先使用组合。
*/