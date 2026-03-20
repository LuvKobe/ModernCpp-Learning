#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

// 使用RAII思想设计的SmartPtr类
//template<class T>
//class SmartPtr 
//{
//public:
//	SmartPtr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//
//	~SmartPtr()
//	{
//		cout << "delete: " << _ptr << endl;
//		if (_ptr)
//			delete _ptr;
//	}
//private:
//	T* _ptr;
//};

//
//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("除0错误");
//	return a / b;
//}

//void Func()
//{
//	// 1、如果p1这里new 抛异常会如何？
//	// 2、如果p2这里new 抛异常会如何？
//	// 3、如果div调用这里又会抛异常会如何？
//	int* p1 = new int;
//	int* p2 = new int;
//	cout << div() << endl;
//	delete p1;
//	delete p2;
//}



//void Func()
//{
//	SmartPtr<int> sp1(new int);
//	SmartPtr<int> sp2(new int);
//
//	cout << div() << endl;
//}
//
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	return 0;
//}


// 使用RAII思想设计的SmartPtr类
template<class T>
class SmartPtr
{
public:
    // 构造
    SmartPtr(T* ptr = nullptr)
        : _ptr(ptr)
    {}

    // 析构
    ~SmartPtr()
    {
        cout << "delete: " << _ptr << endl;
        if (_ptr)
            delete _ptr;
    }

    // 禁止拷贝和赋值
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;

    // 移动构造
    SmartPtr(SmartPtr&& other)
        : _ptr(other._ptr)
    {
        cout << "SmartPtr(SmartPtr&& other) --- 移动构造" << endl;
        other._ptr = nullptr;
    }

    // 移动赋值
    SmartPtr& operator=(SmartPtr&& other)
    {
        cout << "SmartPtr& operator=(SmartPtr&& other) --- 移动赋值" << endl;
        if (this != &other)
        {
            delete _ptr;
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }

    // 重载 * 和 ->
    T& operator*() {
        return *_ptr;
    }

    T* operator->() {
        return _ptr;
    }

private:
    T* _ptr;
};


// 日期类
struct Date
{
    int _year;
    int _month;
    int _day;
};





//int main()
//{
//    SmartPtr<int> sp1(new int);
//    *sp1 = 10;
//    cout << "sp1=" << *sp1 << endl;
//
//    SmartPtr<Date> sp2(new Date);
//    // 需要注意的是这里应该是sparray.operator->()->_year = 2018;
//    // 本来应该是sparray->->_year这里语法上为了可读性，省略了一个->
//    sp2->_year = 2026;
//    sp2->_month = 10;
//    sp2->_day = 5;
//    cout << sp2->_year << "/" << sp2->_month << "/" << sp2->_day << endl;
//
//    return 0;
//}


//int main()
//{
//    SmartPtr<string> sp1(new string("xxxxxx"));
//    SmartPtr<string> sp2(new string("yyyyyy"));
//
//    sp1 = move(sp2);
//
//    return 0;
//}



/////////////////////////////////////////////






//int main()
//{
//    auto_ptr<A> ap1(new A(1));
//
//    // 拷贝
//    auto_ptr<A> ap2(ap1);
//
//    ap1->_a++;  // 崩溃
//
//    ap2->_a++;  // 正常
//
//    return 0;
//}


// 自定义 auto_ptr
namespace edison1
{
    template<class T>
    class auto_ptr
    {
    public:
        // 构造函数
        auto_ptr(T* ptr)
            :_ptr(ptr)
        {}

        // 赋值重载
        auto_ptr<T>& operator=(auto_ptr<T>& ap)
        {
            // 检测是否为自己给自己赋值
            if (this != &ap)
            {
                // 释放当前对象中资源
                if (_ptr)
                    delete _ptr;

                // 转移ap中资源到当前对象中
                _ptr = ap._ptr;
                ap._ptr = NULL;
            }
        }

        // 析构
        ~auto_ptr()
        {
            if (_ptr)
            {
                cout << "delete: " << _ptr << endl;
                delete _ptr;
            }
        }

        // 重载 * 和 ->，能够像指针一样使用
        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

        // 拷贝构造
        // ap2(ap1)
        auto_ptr(auto_ptr<T>& sp)
            :_ptr(sp._ptr)
        {
            // 管理权转移
            sp._ptr = nullptr; // 把 ap1 的内容给置空
        }

    private:
        T* _ptr;
    };
}

//int main()
//{
//    edison::auto_ptr<A> ap1(new A(10));
//
//    // 拷贝
//    edison::auto_ptr<A> ap2(ap1);
//
//    return 0;
//}


////////////////////////////////////////////////////////////////
//
//
// 自定义类
//class A
//{
//public:
//    // 构造
//    A(int a = 0)
//        :_a(a)
//    {
//        cout << "A(int a = 0) --- 构造" << endl;
//    }
//
//    // 析构
//    ~A()
//    {
//        cout << "~A() --- 析构" << endl;
//    }
//    //private:
//    int _a;
//};



//
//int main()
//{
//    unique_ptr<A> up1(new A(10));
//    unique_ptr<A> up2(new A(20));
//
//    // 拷贝
//    unique_ptr<A> up3(up1);
//
//    return 0;
//}



namespace edison2
{
    template<class T>
    class unique_ptr
    {
    public:
        // 构造函数
        unique_ptr(T* ptr)
            :_ptr(ptr)
        {}

        // 析构
        ~unique_ptr()
        {
            if (_ptr)
            {
                cout << "delete: " << _ptr << endl;
                delete _ptr;
            }
        }

        // 重载 * 和 ->，能够像指针一样使用
        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

        // 禁止拷贝构造和赋值重载
        unique_ptr(const unique_ptr<T>& sp) = delete;
        unique_ptr<T>& operator=(const unique_ptr<T>& sp) = delete;
    
    private:
        T* _ptr;
    };
}

//int main()
//{
//    edison::unique_ptr<A> up1(new A(10));
//    edison::unique_ptr<A> up2(new A(20));
//
//    // 拷贝
//    edison::unique_ptr<A> up3(up1);
//
//    return 0;
//}














//////////////////////////////////////////////////////////////


// 自定义类
class A
{
public:
    // 构造
    A(int a = 0)
        :_a(a)
    {
        cout << "A(int a = 0) --- 构造" << endl;
    }

    // 析构
    ~A()
    {
        cout << "~A() --- 析构" << endl;
    }
    //private:
    int _a;
};

#include <mutex>




//int main()
//{
//    // C++11
//    edison::shared_ptr<A> sp1(new A(10));
//    edison::shared_ptr<A> sp2(new A(20));
//
//    // 拷贝
//    edison::shared_ptr<A> sp3(sp1);
//    edison::shared_ptr<A> sp4(sp2);
//    edison::shared_ptr<A> sp5(sp4);
//
//    sp1->_a++;
//    sp3->_a++;
//
//    return 0;
//}




//int main()
//{
//    // C++11
//    edison::shared_ptr<A> sp1(new A(10));
//    edison::shared_ptr<A> sp3(new A(30));
//    edison::shared_ptr<A> sp5(new A(50));
//
//    // 赋值操作
//    sp1 = sp5;
//    sp3 = sp5;
//
//    return 0;
//}


namespace edison
{
    template<class T>
    class shared_ptr
    {
    public:
        // 构造函数
        shared_ptr(T* ptr = nullptr)
            :_ptr(ptr)
            , _pConut(new int(1)) // 当有资源来的时候，就创建一个计数
        {}

        // 析构
        ~shared_ptr()
        {
            // 当计数为0的时候，就进行释放
            if (--(*_pConut) == 0)
            {
                cout << "delete: " << _ptr << endl;
                delete _ptr;
                delete _pConut;
            }
        }

        // 重载 * 和 ->，能够像指针一样使用
        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

        // 拷贝构造
        shared_ptr(const shared_ptr<T>& sp)
            :_ptr(sp._ptr)
            , _pConut(sp._pConut)
        {
            ++(*_pConut); // 对计数进行++操作
        }

        // 赋值重载
        shared_ptr<T>& operator=(const shared_ptr<T>& sp)
        {
            // _ptr != sp._ptr 防止自己给自己赋值
            if (_ptr == sp._ptr)
            {
                return *this;
            }

            if (--(*_pConut) == 0)
            {
                delete _ptr;
                delete _pConut;
            }

            _ptr = sp._ptr;
            _pConut = sp._pConut;
            ++(*_pConut);

            return *this;
        }

        // 统计引用计数的个数
        int use_count() const 
        {
            return *_pConut;
        }

        // 获取原生指针
        T* get() const 
        {
            return _ptr;
        }

    private:
        T* _ptr;
        int* _pConut;  // 引用计数
    };

    template<class T>
    class weak_ptr
    {
    public:
        // 无参构造
        weak_ptr()
            :_ptr(nullptr)
        {}

        // 用 shared_ptr 来构造
        weak_ptr(const shared_ptr<T>& sp)
            :_ptr(sp.get())
        {}

        // 用 shared_ptr 来赋值
        weak_ptr<T>& operator=(const shared_ptr<T>& sp)
        {
            _ptr = sp.get();
            return *this;
        }

        // 重载 * 和 ->，能够像指针一样使用
        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

    private:
        T* _ptr;
    };
}

struct Node
{
    A _val;
    edison::weak_ptr<Node> _next;
    edison::weak_ptr<Node> _prev;
};

int main()
{
    // 智能指针
    edison::shared_ptr<Node> sp1(new Node);
    edison::shared_ptr<Node> sp2(new Node);

    cout << "链接前: " 
        << "sp1.use_count=" << sp1.use_count() 
        << " sp2.use_count= " << sp1.use_count() 
    << endl;

    //
    sp1->_next = sp2;
    sp2->_prev = sp1;

    cout << "链接后: " << "sp1.use_count=" << sp1.use_count() << " sp2.use_count= " << sp2.use_count() << endl;

    return 0;
}