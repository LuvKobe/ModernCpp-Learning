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
class Person
{
public:
    // 构造函数
    Person(const string& name = "edison")
        :_name(name)
    {
        cout << "调用构造函数Person()" << endl;
    }

    // 拷贝构造函数
    Person(const Person& p)
        :_name(p._name)
    {
        cout << "调用拷贝构造函数Person(const Person& p)" << endl;
    }

    //赋值运算符重载函数
    Person& operator=(const Person& p)
    {
        cout << "调用赋值运算符重载函数operator=(const Person& p)" << endl;
        /*
        如果 this == &p，说明你执行了 a = a，也就是自赋值，这时不需要做任何操作，否则可能会引发错误或浪费资源。
        Person a;
        a = a; // 会触发自赋值
        */
        if (this != &p)    // &p 是传入对象的地址。
        {
            // 执行实际的赋值，将传入对象 p 的 _name 成员赋值给当前对象的 _name。
            // 因为 _name 是 string 类型，它的赋值操作会调用 string 类的 operator=，深拷贝内容。
            _name = p._name;
        }
        return *this;
    }

    // 析构函数
    ~Person()
    {
        cout << "调用析构函数~Person()" << endl;
    }
private:
    string _name;
};

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
void test1()
{
    Person a("edison"); // 调用构造函数
    Person b(a); // 调用拷贝构造函数

    cout << endl;

    Person c;
    c.operator=(b); // 调用赋值运算符重载函数
}

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
class Student : public Person
{
public:
    // 构造函数
    Student(const string& name, int id)
        :Person(name) //调用父类的构造函数初始化父类的那一部分成员
        , _stuId(id) //初始化子类的成员
    {
        cout << "调用构造函数Student()" << endl;
    }

    // 拷贝构造函数
    Student(const Student& s)
        :Person(s) //调用父类的拷贝构造函数完成父类成员的拷贝构造
        , _stuId(s._stuId) //拷贝构造派生类的成员
    {
        cout << "调用拷贝构造函数Student(const Student& s)" << endl;
    }

    // 赋值运算符重载函数
    Student& operator=(const Student& s)
    {
        cout << "调用赋值运算符重载函数operator=(const Student& p)" << endl;
        if (this != &s)
        {
            Person::operator=(s); //调用父类的operator=完成基类成员的赋值
            _stuId = s._stuId; //完成子类成员的赋值
        }
        return *this;
    }

    // 析构函数
    ~Student()
    {
        cout << "调用析构函数~Student()" << endl;
        // 子类的析构函数会在被调用完成后自动调用父类的析构函数
    }
private:
    int _stuId;
};

// 测试子类
void test2()
{
    Student s1("张三", 001); // 调用构造函数
    cout << endl;

    Student s2(s1); // 调用拷贝构造函数
    cout << endl;

    Student s3("李四", 002); // 调用构造函数
    cout << endl;

    s3.operator=(s1); // 调用赋值运算符重载函数
    cout << endl;
}

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

int main()
{
    test2();
    return 0;
}

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