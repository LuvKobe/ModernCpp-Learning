#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <map>
#include <string>

using namespace std;


class HeapOnly
{
public:
	static HeapOnly* CreateObject()
	{
		cout << "static HeapOnly* CreateObject()" << endl;
		return new HeapOnly;
	}

private:
	// 构造函数私有
	HeapOnly() {}

	// C++98
	// 1.只声明, 不实现。因为实现可能会很麻烦，而你本身不需要。
	// 2.声明成私有
	HeapOnly(const HeapOnly&); // 拷贝构造私有

	// C++11
	//HeapOnly(const HeapOnly&) = delete;
};

//int main()
//{
//	HeapOnly* hp3 = HeapOnly::CreateObject();
//
//	return 0;
//}



/////////////////////////////////////////


//class StackOnly
//{
//public:
//    static StackOnly CreateObj()
//    {
//        // 这里和堆不同的是：需要返回一个对象
//        StackOnly st;
//        return st;
//
//        // 写法等价于下面
//        //return StackOnly();
//    }
//
//    // 对一个类实现专属的【operator new】
//    // 禁掉【operator new】以后，可以把下面用 【new + 调用拷贝构造】申请对象给禁掉
//    void* operator new(size_t size) = delete;
//    void operator delete(void* p) = delete;
//
//private:
//    // 构造函数私有
//    StackOnly()
//        :_a(0)
//    {}
//
//private:
//    int _a;
//};
//
//int main()
//{
//    StackOnly st1 = StackOnly::CreateObj();
//    StackOnly copy(st1);
//
//    // new = operator new + 构造
//    StackOnly* st2 = new StackOnly(st1);
//
//    return 0;
//}

/////////////////////////////////////////




// 父类
class NonInherit
{
public:
    // 在类内部创建对象，并把对象 “返回出去”
    static NonInherit GetInstance()
    {
        return NonInherit();
    }

private:
    // 构造函数私有
    NonInherit()
    {}
};

// 子类
class B : public NonInherit
{
public:
    //B() {} // 编译报错：无法访问基类构造函数
};




// 父类
//class A final
//{
//    // ....
//};
//
//// 直接编译报错
//class B : public A 
//{
//
//}; 


///////////////////////////////////////////////////



//class Singleton
//{
//public:
//	// 第三步：提供一个获取单例的接口
//	static Singleton* GetInstance()
//	{
//		return &m_instance;
//	}
//
//public:
//	void Add(const pair<string, string>& kv)
//	{
//		_dict[kv.first] = kv.second;
//	}
//
//	void Print()
//	{
//		for (const auto& e : _dict)
//		{
//			cout << e.first << ":" << e.second << endl;
//		}
//		cout << endl;
//	}
//
//private:
//	// 第一步：构造函数私有
//	Singleton() {};
//
//	// 第二步：C++98写法：防拷贝
//	//Singleton(Singleton const&);
//	//Singleton& operator=(Singleton const&);
//
//	// or
//
//	// 第二步：C++11写法：防拷贝
//	Singleton(Singleton const&) = delete;
//	Singleton& operator=(Singleton const&) = delete;
//
//private:
//	map<string, string> _dict;
//
//	// 1.1 必须在类里面进行声明
//	static Singleton m_instance;
//};
//
//// 1.2 然后在类外面定义
//Singleton Singleton::m_instance;  // 在程序入口之前就完成单例对象的初始化




//int main()
//{
//	Singleton* s1 = Singleton::GetInstance();
//	Singleton* s2 = Singleton::GetInstance();
//
//	cout << "s1: " << &s1 << endl;
//	cout << "s2: " << &s2 << endl;
//
//	return 0;
//}


//// 饿汉模式
//class Singleton
//{
//public:
//	// 第三步：提供一个获取单例的接口
//	static Singleton* GetInstance()
//	{
//		return &m_instance;
//	}
//
//public:
//	void Add(const pair<string, string>& kv)
//	{
//		_dict[kv.first] = kv.second;
//	}
//
//	void Print()
//	{
//		for (const auto& e : _dict)
//		{
//			cout << e.first << ":" << e.second << endl;
//		}
//		cout << endl;
//	}
//
//private:
//	// 第一步：构造函数私有
//	Singleton() {};
//
//	// 第二步：C++11写法：防拷贝
//	Singleton(Singleton const&) = delete;
//	Singleton& operator=(Singleton const&) = delete;
//
//private:
//	map<string, string> _dict;
//
//	// 1.1 必须在类里面进行声明
//	static Singleton m_instance;
//};
//
//// 1.2 然后在类外面定义
//Singleton Singleton::m_instance;  // 在程序入口之前就完成单例对象的初始化
//
//
//int main()
//{
//	// 定义
//	Singleton::GetInstance()->Add({ "xxx", "111" });
//	Singleton::GetInstance()->Add({ "yyy", "222" });
//	Singleton::GetInstance()->Add({ "zzz", "333" });
//	Singleton::GetInstance()->Add({ "abc", "123" });
//
//	// 打印
//	Singleton::GetInstance()->Print();
//
//	return 0;
//}


//// 懒汉模式
//class Singleton
//{
//public:
//	// 提供获取单例的接口
//	static Singleton* GetInstance()
//	{
//		if (m_instance == nullptr)
//		{
//			// 第一次调用 GetInstance 的时候创建单例对象
//			m_instance = new Singleton;
//		}
//		return m_instance;
//	}
//
//	// 释放接口
//	static void DelInstance()
//	{
//		if (m_instance)
//		{
//			delete m_instance;
//			m_instance = nullptr;
//		}
//	}
//
//public:
//	void Add(const pair<string, string>& kv)
//	{
//		_dict[kv.first] = kv.second;
//	}
//
//	void Print()
//	{
//		for (const auto& e : _dict)
//		{
//			cout << e.first << ":" << e.second << endl;
//		}
//		cout << endl;
//	}
//
//private:
//	// 构造函数私有
//	Singleton() {};
//
//	// 析构函数私有
//	~Singleton()
//	{
//		cout << "~Singleton()" << endl;
//
//		// 把 map 数据写入到文件中
//		FILE* fp = fopen("map.txt", "w");
//		for (const auto& e : _dict)
//		{
//			fputs(e.first.c_str(), fp);
//			fputs(":", fp);
//			fputs(e.second.c_str(), fp);
//			fputs("\n", fp);
//		}
//	}
//
//	// 防拷贝
//	Singleton(Singleton const&) = delete;
//	Singleton& operator=(Singleton const&) = delete;
//
//private:
//	map<string, string> _dict;
//
//	// 指针形式的单例
//	static Singleton* m_instance;
//
//public:
//	class GC
//	{
//	public:
//		~GC()
//		{
//			Singleton::DelInstance();
//		}
//	};
//	static GC _gc;
//};
//
//// 类外初始化
//Singleton* Singleton::m_instance = nullptr;
//Singleton::GC Singleton::_gc;


//class GC
//{
//public:
//	~GC()
//	{
//		Singleton::DelInstance();
//	}
//};
//
//// 创建一个 GC 对象, 这个对象出了作用域就会调用析构
//// 那么它调用析构函数的时候，就会去调用 DelInstance
//GC gc;



//int main()
//{
//	// 定义
//	Singleton::GetInstance()->Add({ "xxx", "111" });
//	Singleton::GetInstance()->Add({ "yyy", "222" });
//	Singleton::GetInstance()->Add({ "zzz", "333" });
//	Singleton::GetInstance()->Add({ "abc", "123" });
//
//	// 打印
//	Singleton::GetInstance()->Print();
//
//	// 重新定义
//	Singleton::GetInstance()->Add({ "www", "000" });
//	Singleton::GetInstance()->Print();
//
//	return 0;
//}





////////////////////////////////////////////



#include <mutex>
#include <thread>


//// 懒汉模式单例（双检锁）
//class Singleton
//{
//public:
//    // 提供获取单例的接口（线程安全版）
//    static Singleton* GetInstance()
//    {
//        // 双检查
//        if (m_instance == nullptr)
//        {
//            unique_lock<mutex> lock(_mtx);
//            if (m_instance == nullptr)
//            {
//                m_instance = new Singleton;
//            }
//        }
//        return m_instance; // 修正：保证始终返回实例
//    }
//
//    void PrintAddress()
//    {
//        cout << "Singleton instance address: " << this << endl;
//    }
//
//private:
//    Singleton() {}  // 构造函数私有
//    Singleton(const Singleton&) = delete;
//    Singleton& operator=(const Singleton&) = delete;
//
//private:
//    map<string, string> _dict;  // 示例资源
//    static Singleton* m_instance;
//    static mutex _mtx;  // 锁对象
//};
//
//// 类外初始化
//Singleton* Singleton::m_instance = nullptr;
//mutex Singleton::_mtx;
//
//int main()
//{
//    // 启动多个线程同时获取单例
//    thread t1([]() { Singleton::GetInstance()->PrintAddress(); });
//    thread t2([]() { Singleton::GetInstance()->PrintAddress(); });
//    thread t3([]() { Singleton::GetInstance()->PrintAddress(); });
//
//    t1.join();
//    t2.join();
//    t3.join();
//
//    return 0;
//}


////////////////////////////////////////////////////////


// 懒汉模式单例
class Singleton
{
public:
    // 提供获取单例的接口
    static Singleton& GetInstance()
    {
        // 局部的静态对象会在第一次调用时初始化
        static Singleton inst;
        return inst;
    }

private:
    Singleton() {}  // 构造函数私有
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

int main()
{
    Singleton::GetInstance();
    return 0;
}