#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
int main()
{
	double x = 1.1, y = 2.2;

	// 右值引用
	int&& rr1 = 10;
	double&& rr2 = x + y;
	double&& rr3 = fmin(x, y);

	// 左值引用给右值取别名
	// const 左值引用可以
	const int& r1 = 10;
	const double& r2 = x + y;

	return 0;
}*/


// 自定义string类
namespace edison
{
    class string
    {
    public:
        typedef char* iterator;

        iterator begin()
        {
            return _str; // 返回字符串中第一个字符的地址
        }

        iterator end()
        {
            return _str + _size; // 返回字符串中最后一个字符的后一个字符的地址
        }

        // 构造函数
        string(const char* str = "")
            : _size(strlen(str)), _capacity(_size)
        {
            cout << "string(const char* str) -- 构造" << endl;

            _str = new char[_capacity + 1]; // 为存储字符串开辟空间（多开一个用于存放'\0'）
            strcpy(_str, str);              // 将C字符串拷贝到已开好的空间
        }

        // 交换两个对象的数据
        void swap(string& s)
        {
            // 调用库里的swap
            ::swap(_str, s._str);           // 交换两个对象的C字符串
            ::swap(_size, s._size);         // 交换两个对象的大小
            ::swap(_capacity, s._capacity); // 交换两个对象的容量
        }

        // 拷贝构造函数（现代写法）
        string(const string& s)
            : _str(nullptr), _size(0), _capacity(0)
        {
            cout << "string(const string& s) -- 拷贝构造" << endl;

            string tmp(s._str); // 调用构造函数，构造出一个C字符串为s._str的对象
            swap(tmp);          // 交换这两个对象
        }

        // ===== 新增：移动构造函数 =====
        // 接收右值引用（&&），转移资源而非拷贝
        string(string&& s) noexcept
            : _str(nullptr), _size(0), _capacity(0)
        {
            cout << "string(string&& s) -- 移动构造（无拷贝）" << endl;
            swap(s);  // 将 s 的资源全部窃取过来
        }

        // 赋值运算符重载（现代写法）
        string& operator=(const string& s)
        {
            cout << "string& operator=(const string& s) -- 赋值重载（深拷贝）" << endl;

            string tmp(s); // 用s拷贝构造出对象tmp
            swap(tmp);     // 交换这两个对象
            return *this;  // 返回左值（支持连续赋值）
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
            delete[] _str;  // 释放_str指向的空间
            _str = nullptr; // 及时置空，防止非法访问
            _size = 0;      // 大小置0
            _capacity = 0;  // 容量置0
        }

        //[]运算符重载
        char& operator[](size_t i)
        {
            assert(i < _size); // 检测下标的合法性
            return _str[i];    // 返回对应字符
        }

        // 改变容量，大小不变
        void reserve(size_t n)
        {
            if (n > _capacity) // 当n大于对象当前容量时才需执行操作
            {
                char* tmp = new char[n + 1];   // 多开一个空间用于存放'\0'
                strncpy(tmp, _str, _size + 1); // 将对象原本的C字符串拷贝过来（包括'\0'）
                delete[] _str;                 // 释放对象原本的空间
                _str = tmp;                    // 将新开辟的空间交给_str
                _capacity = n;                 // 容量跟着改变
            }
        }

        // 尾插字符
        void push_back(char ch)
        {
            if (_size == _capacity) // 判断是否需要增容
            {
                reserve(_capacity == 0 ? 4 : _capacity * 2); // 将容量扩大为原来的两倍
            }
            _str[_size] = ch;       // 将字符尾插到字符串
            _str[_size + 1] = '\0'; // 字符串后面放上'\0'
            _size++;                // 字符串的大小加一
        }

        //+=运算符重载
        string& operator+=(char ch)
        {
            push_back(ch); // 尾插字符串
            return *this;  // 返回左值（支持连续+=）
        }

        // 返回C类型的字符串
        const char* c_str() const
        {
            return _str;
        }

    private:
        char* _str;
        size_t _size;
        size_t _capacity;
    };
}


//void func1(edison::string s)
//{}
//
//void func2(const edison::string& s)
//{}



/*
int main()
{
    edison::string s1("hello world"); 

    // func1 和 fun2 的调用我们可以看到左值引用做参数减少了拷贝，提高效率的使用场景和价值
    func1(s1); // 值传递（一定会拷贝）
    func2(s1); // 引用传递（无拷贝）

    char ch = 'a';

    //edison::string operator+=(char ch);  //传值返回存在深拷贝
    //edison::string& operator+=(char ch); //传左值引用没有拷贝提高了效率
    s1 += '!';

    return 0;
}*/

// 1. 传值返回：返回 edison::string 对象的副本（触发深拷贝）
//edison::string returnByValue() 
//{
//    edison::string s("hello");  // 创建局部string对象
//    s += '!';                   // 修改对象：尾插字符
//    cout << "returnByValue 中局部对象地址：" << &s << endl;
//    return s;                   // 传值返回：触发拷贝构造，拷贝局部s到临时对象
//}
//
//// 2. 传左值引用返回：返回 edison::string 对象的引用（无拷贝）
//edison::string globalStr("world"); // 全局string对象（生命周期贯穿程序）
//
//edison::string& returnByLvalueRef() 
//{
//    globalStr += '!';            // 修改全局对象
//    cout << "returnByLvalueRef 中全局对象地址：" << &globalStr << endl;
//    return globalStr;            // 返回引用：无任何拷贝，直接指向全局对象
//}

//int main() 
//{
//    cout << "===== 测试传值返回（触发深拷贝）=====" << endl;
//    // 接收传值返回的对象：触发拷贝构造（深拷贝）
//    edison::string valStr = returnByValue();
//    cout << "main中valStr的地址：" << &valStr << endl;
//    cout << "valStr的内容：" << valStr.c_str() << endl;
//    cout << "----------------------------------------" << endl;
//    cout << endl;
//
//    cout << "===== 测试左值引用返回（无拷贝）=====" << endl;
//    // 接收左值引用返回：无拷贝，直接绑定到全局对象
//    edison::string& refStr = returnByLvalueRef();
//    cout << "main中refStr的地址：" << &refStr << endl;
//    cout << "refStr的内容：" << refStr.c_str() << endl;
//    // 验证：refStr 和 全局对象是同一个（地址完全相同）
//    cout << "全局对象globalStr的地址：" << &globalStr << endl;
//
//    return 0;
//}


//// 全局对象：生命周期贯穿整个程序，可安全返回其左值引用
//edison::string global_str("hello reference return");
//
//// 函数1：传值返回（一定会触发拷贝构造，产生返回值副本）
//edison::string return_by_value()
//{
//    global_str += 'c';
//    return global_str; // 传值返回：触发深拷贝
//}
//
//// 函数2：左值引用返回（无拷贝，直接返回对象本身）
//const edison::string& return_by_lvalue_ref()
//{
//    global_str += 'n';
//    return global_str; // 引用返回：无任何拷贝
//}

//// 主函数
//int main()
//{
//    // 测试传值返回：触发深拷贝
//    edison::string s1 = return_by_value();
//
//    // 测试左值引用返回：无拷贝，直接绑定全局对象
//    const edison::string& s2 = return_by_lvalue_ref();
//
//    // 验证：s2 与全局对象地址相同（无拷贝），s1 是新对象（有拷贝）
//    cout << "s1（传值返回）地址：" << &s1 << endl;
//    cout << "s2（引用返回）地址：" << &s2 << endl;
//
//    cout << "全局对象地址：" << &global_str << endl;
//
//    return 0;
//}


//// 错误示例函数：返回局部对象的左值引用（严禁使用！）
// edison::string& wrong_return_ref()
// {
//     edison::string local_str("local object"); // 局部对象，函数结束后销毁
//     return local_str; // 错误：返回悬空引用，访问会导致未定义行为
// }
//
// int main()
// {
//     // 接收局部对象的引用（此时localStr已销毁，引用悬空）
//     edison::string& s3 = wrong_return_ref();
//     cout << "main中悬空引用的地址：" << &s3 << endl;
//
//     // 访问悬空引用：未定义行为（可能输出乱码、程序崩溃）
//     cout << "main中悬空引用的内容：" << s3.c_str() << endl;
//
//     return 0;
// }





// 正确示例：返回局部对象的值（传值返回，触发深拷贝但安全）
//edison::string right_return_ref()
//{
//    edison::string local_str("local object"); // 局部对象
//    cout << "right_return_ref中局部对象地址：" << &local_str << endl;
//    return local_str; // 传值返回，拷贝localStr的副本，原局部对象销毁
//}

//int main()
//{
//    // 接收传值返回的副本（深拷贝，安全）
//    edison::string s3 = right_return_ref();
//    cout << "main中副本对象的地址：" << &s3 << endl;
//
//    // 访问副本对象：安全且正确
//    cout << "main中副本对象的内容：" << s3.c_str() << endl;
//
//    return 0;
//}











//edison::string func()
//{
//    edison::string str("helloworld");
//
//    return str;
//}
//
//int main()
//{
//    edison::string ret;
//    
//    ret = func();
//
//    return 0;
//}




/*
前面我们可以看到，【左值引用】既可以引用【左值】和又可以引用【右值】，那为什么 C++11 还要提出【右值引用】呢？是不是化蛇添足呢？

其实左值引用提高了效率，但仍有短板，C++11 引入右值引用，就是为了解决左值引用解决不了的问题。而这个关键问题就是：**当函数返回局部对象时，无法用左值引用避免拷贝**。

下面我们来看看【左值引用】的短板，并且【右值引用】是如何补齐这个短板的。

左值引用作为 “函数参数” 可以完全避免拷贝，但作为 “函数返回值” 却不能完全避免拷贝。


*/



//edison::string func()
//{
//    edison::string str("hello world");
//    
//    return str;
//}
//
//int main()
//{
//    edison::string s1;
//
//    s1 = func();
//
//    return 0;
//}



void Func(int& x)
{
    cout << "左值引用" << endl;
}

void Func(const int& x)
{
    cout << "const 左值引用" << endl;
}

void Func(int&& x)
{
    cout << "右值引用" << endl;
}

void Func(const int&& x)
{
    cout << "const 右值引用" << endl;
}

// 万能引用：既可以接收左值，又可以接收右值
// std::forward<T>(t)在传参的过程中保持了t的原生类型属性。
template <typename T>
void PerfectForward(T&& t)
{
    Func(std::forward<T>(t));
}

//int main()
//{
//    PerfectForward(10);     // 右值
//
//    int a = 10;
//    PerfectForward(a);       // 左值
//    PerfectForward(move(a)); // 右值
//
//    const int b = 20;
//    PerfectForward(b);       // const 左值
//    PerfectForward(move(b)); // const 右值
//
//    return 0;
//}



//#include "list.h"


namespace edison
{
    // 链表结点
    template <class T>
    struct ListNode
    {
        ListNode* _next = nullptr;
        ListNode* _prev = nullptr;
        T _data;
    };

    //
    template <class T>
    class list
    {
        typedef ListNode<T> node;

    public:
        // 构造函数
        list()
        {
            _head = new node;
            _head->_next = _head;
            _head->_prev = _head;
        }

        // 左值引用版本的push_back
        void push_back(const T& x)
        {
            insert(_head, x);
        }

        // 右值引用版本的push_back
        void push_back(T&& x)
        {
            insert(_head, std::forward<T>(x)); // 完美转发
        }

        // 左值引用版本的insert
        void insert(node* pos, const T& x)
        {
            node* prev = pos->_prev;
            node* newnode = new node;
            newnode->_data = x;

            prev->_next = newnode;
            newnode->_prev = prev;
            newnode->_next = pos;
            pos->_prev = newnode;
        }

        // 右值引用版本的insert
        void insert(node* pos, T&& x)
        {
            node* prev = pos->_prev;
            node* newnode = new node;
            newnode->_data = std::forward<T>(x); // 完美转发

            prev->_next = newnode;
            newnode->_prev = prev;
            newnode->_next = pos;
            pos->_prev = newnode;
        }

    private:
        node* _head; // 指向链表头结点的指针
    };
}

//int main()
//{
//	edison::list<edison::string> lt;
//
//    edison::string s1("111111111111111111111");
//	lt.push_back(s1);
//
//	cout << endl << endl;
//    edison::string s2("111111111111111111111");
//    lt.push_back(move(s2));
//
//    cout << endl << endl;
//	lt.push_back("22222222222222222222222222222");
//
//	return 0;
//}



int main()
{
    // 这里s1是左值，调用的是拷贝构造
    edison::string s1("hello world");

    cout << endl;
    edison::string s2(s1);

    cout << endl;
    edison::string s3(move(s1));

    return 0;
}