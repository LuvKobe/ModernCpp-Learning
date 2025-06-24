//命名规范
// 编码 --> 预处理 --> 编译+链接 --> 生成

/*
#define MAX_PATH_LEN 256 // 常量, 全大写

int g_sys_flag; // 全局变量, 加 g_ 前缀

namespace linux_sys // 名字空间, 全小写
{
    void get_rlimit_core(); // 函数, 全小写
}

class FilePath final
{
public:
    void set_path(const string& str); // 函数, 全小写
private:
    string m_path; // 成员变量, m_ 前缀
    int m_level; // 成员变量, m_ 前缀
};
*/

#include <iostream>
using namespace std;

/*
template<int N>
struct fib
{   
    static_assert(N >= 0, "N >= 0");
    static const int value = fib<N - 1>::value + fib<N - 2>::value;
};

template<>
struct fib<0>
{
    static const int value = 1;
};

template<>
struct fib<1>
{
    static const int value = 1;
};

int main()
{
    cout << fib<2>::value << endl;
    cout << fib<3>::value << endl;
    cout << fib<4>::value << endl;
    cout << fib<5>::value << endl;

    return 0;
}
*/

/*
// final : 显示的禁用继承
class DemoClass final
{ 

};

// 可以被继承
class InterFace 
{
    
};

// 只用public继承
class Implement final :
        public InterFace
{
 
};
*/

// cpp98 ：构造函数、析构函数、拷贝构造函数、拷贝赋值函数
// cpp11 ：右值(Rvalue)、转移(Move)
//         转移构造函数、转移赋值函数

// 现代C++一个类会有六大基本函数：三个构造、两个赋值、一个析构

/*
class DemoClass final
{
public:
    DemoClass() = default; // 告诉编译器使用默认实现
    ~DemoClass() = default;

    DemoClass(const DemoClass&) = delete; // 禁止拷贝构造
    DemoClass& operator=(const DemoClass&) = delete; // 禁止拷贝赋值

    explicit DemoClass(const string_type& str) // 显式单参构造函数
    {  }
    explicit operator bool() // 显式类型为bool
    {  }
};
*/

// 委托构造
/*
class DemoClass final
{
private:
    int a;
public:
    DemoClass(int x) // 普通构造函数
        : a(x) 
    {

    }

    DemoClass()  // 无参数的构造函数
        : DemoClass(0) // 给出默认值, 委托给第一个构造函数
    {

    }

    DemoClass(const string& s) // 字符串参数构造函数
        : DemoClass(stoi(s)) // 转换成整数, 再委托给第一个构造函数
    {

    }
};
*/

#include <string>
#include <vector>

/*
class DemoInit final
{
private:
    int a = 0;
    string s = "hello"; 
    vector<int> v{1, 2, 3}; // 容器成员, 使用花括号的初始化列表
public:
    DemoInit() = default;
    ~DemoInit() = default;
public:
    DemoInit(int x) 
        : a(x)
    {
        ;
    }
    void DemoPrint()
    {
        cout << "a = " << a << endl;
        cout << "s = " << s << endl;
        for (int i = 0; i < v.size(); i ++)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    DemoInit di(100);
    di.DemoPrint();
    return 0;
}
*/

#include <set>

// cpp11新增using关键字, 等价于typedef
using uint_t = unsigned int;
typedef unsigned int uint_t; 

class KafkaConfig
{

};

class DemoClass final
{
public:
    using this_type = DemoClass;    // 给自己起个别名
    using kafka_conf_type = KafkaConfig;    // 给外部类起别名

public:
    using string_type = std::string;    // 字符串类型别名
    using uint32_type = uint32_t;   // 整数类型别名

    using set_type = std::set<int>;     // 集合类型别名
    using vector_type = std::vector<std::string>;   // 容器类型别名

private:
    string_type m_name = "tom";
    uint32_type m_age = 23;
    set_type m_books;

private:
    kafka_conf_type m_conf;
};

/*
今天我们谈了“面向对象编程”，这节课的内容也比较多，我划一下重点。

1、“面向对象编程”是一种设计思想，要点是“抽象”和“封装”，“继承”“多态”是衍生出的特性，不完全符合现实世界。

2、在 C++ 里应当少用继承和虚函数，降低对象的成本，绕过那些难懂易错的陷阱。

3、使用特殊标识符“final”可以禁止类被继承，简化类的层次关系。

4、类有六大基本函数，对于重要的构造 / 析构函数，可以使用“= default”来显式要求编译器使用默认实现。

5、“委托构造”和“成员变量初始化”特性可以让创建对象的工作更加轻松。

7、使用 using 或 typedef 可以为类型起别名，既能够简化代码，还能够适应将来的变化。
*/