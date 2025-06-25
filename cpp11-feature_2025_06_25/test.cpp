#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;


// 自动 -- 类型 -- 推导
// “自动”就是让计算机去做，而不是人去做，相对的是“手动”。
// “类型”指的是操作目标，出来的是编译阶段的类型，而不是数值。
// “推导”就是演算、运算，把隐含的值给算出来。

/*
因为 C++ 是一种静态强类型的语言，任何变量都要有一个确定的类型，否则就不能用。
在“自动类型推导”出现之前，我们写代码时只能“手动推导”，也就是说，在声明变量的
时候，必须要明确地给出类型
*/

/*
int main()
{
    int i = 0;      // 整数变量，类型很容易知道
    double x = 1.0;   // 浮点数变量，类型很容易知道
    std::string str = "hello";    // 字符串变量，有了名字空间，麻烦了一点
    
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};    // 关联数组，名字空间加模板参数，很麻烦; 使用初始化列表的形式
    std::map<int, std::string>::const_iterator iter = m.begin();  // 内部子类型，超级麻烦
    
    // ？？？ = bind1st(std::less<int>(), 2);  // 根本写不出来
    
    return 0;
}
*/

/*
int main()
{
    auto i = 0;      // 自动推导为int类型
    auto x = 1.0;   // 自动推导为double类型
    auto str = "hello";    // 自动推导为const char[6]类型
    
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}}; // 自动推导不出来
    auto iter = m.begin();  // 自动推导为map内部的迭代器类型
    
    auto  f = bind1st(std::less<int>(), 2);  // 自动推导出类型，具体是啥不知道
    return 0;
}
*/

/*
除了简化代码，auto 还避免了对类型的“硬编码”，也就是说变量类型不是“写死”的，
而是能够“自动”适应表达式的类型。比如，你把 map 改为 unordered_map，那么后面
的代码都不用动。这个效果和类型别名有点像，但你不需要写出 typedef 或
者 using，全由 auto“代劳”

首先，你要知道，auto 的“自动推导”能力只能用在“初始化”的场合。

具体来说，就是赋值初始化或者花括号初始化（初始化列表、Initializer list），变量右边
必须要有一个表达式（简单、复杂都可以）。这样你才能在左边放上 auto，编译器才能找
到表达式，帮你自动计算类型。

如果不是初始化的形式，只是“纯”变量声明，那就无法使用 auto。因为这个时候没有表
达式可以让 auto 去推导

这里还有一个特殊情况，在类成员变量初始化的时候（第 5 讲），目前的 C++ 标准不允
许使用 auto 推导类型
*/

/*
class X final
{
    auto a = 10;  // 错误，类里不能使用auto推导类型
};
*/


/*

总结：

1、auto 总是推导出“值类型”，绝不会是“引用”；

2、auto 可以附加上 const、volatile、*、& 这样的类型修饰符，得到新的类型。

*/


// 认识 decltype

/*
decltype 的形式很像函数，后面的圆括号里就是可用于计算类型的表达式（和 sizeof 有点
类似），其他方面就和 auto 一样了，也能加上 const、*、& 来修饰。
但因为它已经自带表达式，所以不需要变量后面再有表达式，也就是说可以直接声明变量。

*/

// decltype 不仅能够推导出值类型，还能够推导出引用类型，也就是表达式的“原始类型”
/*
int main()
{
    int x = 0;  // 整型变量

    decltype(x) x1;     // 推导为int，x1是int
    decltype(x)& x2 = x;    // 推导为int，x2是int&，引用必须赋值
    decltype(x)* x3;    // 推导为int，x3是int*
    decltype(&x) x4;    // 推导为int*，x4是int*
    decltype(&x)* x5;   // 推导为int*，x5是int**
    decltype(x2) x6 = x2;   // 推导为int&，x6是int&，引用必须赋值

    using int_ptr = decltype(&x);   // int *
    return 0;
}
*/

/*
既然 decltype 类型推导更精确，那是不是可以替代 auto 了呢？

实际上，它也有个缺点，就是写起来略麻烦，特别在用于初始化的时候，表达式要重复两次
（左边的类型计算，右边的初始化），把简化代码的优势完全给抵消了。

所以，C++14 就又增加了一个“decltype(auto)”的形式，既可以精确推导类型，又能像 
auto 一样方便使用。

*/
/*
int main()
{
    int x = 0;  // 整型变量
    decltype(auto) x1 = (x);    // 推导为int&，因为(expr)是引用类型
    return 0;
}
*/

// 使用 auto/decltype
/*
auto 还有一个“最佳实践”，就是“range-based for”，不需要关心容器元素类型、迭
代器返回值和首末位置，就能非常轻松地完成遍历操作。不过，为了保证效率，最好使
用“const auto&”或者“auto&”
*/
/*
int main()
{
    vector<int> v = { 2, 3, 5, 7, 11};  // vector顺序容器
    for (const auto& i : v)     // 常引用方式访问元素，避免拷贝代价
    {
        cout << i << " ";  // 常引用不会改变元素的值
    }
    cout << endl;

    for (auto& i : v)   // 引用方式访问元素
    {
        i ++;   // 可以改变元素的值
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
*/

/*
在 C++14 里，auto 还新增了一个应用场合，就是能够推导函数返回值，这样在写复杂函
数的时候，比如返回一个 pair、容器或者迭代器，就会很省事。
*/
/*

auto get_a_set()    // auto作为函数返回值的占位符
{
    std::set<int> s = {1, 2, 3};
    return s;
}
*/


/*
再来看 decltype 怎么用最合适。

它是 auto 的高级形式，更侧重于编译阶段的类型计算，所以常用在泛型编程里，获取各种
类型，配合 typedef 或者 using 会更加方便。当你感觉“这里我需要一个特殊类型”的时
候，选它就对了。

比如说，定义函数指针在 C++ 里一直是个比较头疼的问题，因为传统的写法实在是太怪异
了。但现在就简单了，你只要手里有一个函数，就可以用 decltype 很容易得到指针类型。
*/

// UNIX信号函数的原型，看着就让人晕，你能手写出函数指针吗？
void (*signal(int signo, void (*func)(int)))(int);

// 使用decltype可以轻松得到函数指针类型
using sig_func_ptr_t = decltype(&signal);

/*
在定义类的时候，因为 auto 被禁用了，所以这也是 decltype 可以“显身手”的地方。

它可以搭配别名任意定义类型，再应用到成员变量、成员函数上，变通地实现 auto 的功能。
*/

class DemoClass final
{
public:
    using set_type = std::set<int>;     // 集合类型别名

public:
    // 构造函数：初始化集合和迭代器
    DemoClass()
        : m_set(),
        m_pos(m_set.begin())
    {}

    // 插入元素
    void insert(int val)
    {
        auto ret = m_set.insert(val);
        if (ret.second && m_pos == m_set.end())
        {
            m_pos = m_set.begin(); // 如果插入第一个元素，更新迭代器
        }
    }

    // 遍历集合并打印元素
    void printElements() const
    {
        cout << "集合元素: ";
        for (auto it = m_set.begin(); it != m_set.end(); ++ it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    // 重置迭代器到开始位置
    void resetIterator()
    {
        m_pos = m_set.begin();
    }

    // 获取下一个元素（简单迭代器演示）
    bool getNext(int& val)
    {
        if (m_pos == m_set.end())
        {
            return false;
        }
        val = *m_pos++;
        return true;
    }

private:
    set_type m_set;   // 使用别名定义成员变量   

    // 使用decltype计算表达式的类型，定义别名
    using iter_type = decltype(m_set.begin());

    // m_pos 类型为 set<int>::iterator
    iter_type m_pos;    // 类型别名定义成员变量
};

int main()
{
    DemoClass de;

    // 插入元素
    de.insert(3);
    de.insert(1);
    de.insert(2);
    de.insert(5);
    de.insert(4);
    de.insert(0);

    // 打印所有元素
    de.printElements();

    // 使用迭代器遍历元素
    cout << "使用迭代器遍历: ";
    int val;
    de.resetIterator();
    while (de.getNext(val))
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
好了，今天我介绍了 C++ 里的“自动类型推导”，简单小结一下今天的内容。

1、“自动类型推导”是给编译器下的指令，让编译器去计算表达式的类型，然后返回给程
序员。

2、auto 用于初始化时的类型推导，总是“值类型”，也可以加上修饰符产生新类型。它的
规则比较好理解，用法也简单，应该积极使用。

3、decltype 使用类似函数调用的形式计算表达式的类型，能够用在任意场合，因为它就是
一个编译阶段的类型。

4、decltype 能够推导出表达式的精确类型，但写起来比较麻烦，在初始化时可以采用 
decltype(auto) 的简化形式。

5、因为 auto 和 decltype 不是“硬编码”的类型，所以用好它们可以让代码更清晰，减少
后期维护的成本。
*/