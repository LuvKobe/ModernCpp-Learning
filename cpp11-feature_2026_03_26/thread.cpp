#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <thread>
#include <vector>
#include <string>

using namespace std;

//void Print(size_t n)
//{
//	for (size_t i = 0; i < n; ++i)
//	{
//		cout << i << endl;
//	}
//}
//
//int main()
//{
//	thread t1(Print, 100);
//	thread t2(Print, 100);
//
//	cout << "线程1: " << t1.get_id() << endl;
//	cout << "线程2: " << t2.get_id() << endl;
//
//
//	t1.join();
//	t2.join();
//
//	return 0;
//}


// 函数
//void ThreadFunc(int a)
//{
//	cout << "Thread1" << a << endl;
//}

// 自定义类
class TF
{
public:
	void operator()()
	{
		cout << "Thread3" << endl;
	}
};



//int main()
//{
//	// 线程函数为函数指针
//	thread t1(ThreadFunc, 10);
//
//	// 线程函数为函数对象
//	TF tf;
//	thread t3(tf);
//
//	// 线程函数为lambda表达式
//	thread t2([] {cout << "Thread2" << endl; });
//
//	t1.join();
//	t2.join();
//	t3.join();
//
//	cout << "Main thread!" << endl;
//	return 0;
//}



//void Print()
//{
//    cout << "thread running" << endl;
//}

//int main()
//{
//    thread t1(Print);
//
//    // thread t2 = t1;            // 错误：不允许拷贝构造
//    // t2 = t1;                  // 错误：不允许拷贝赋值
//
//    thread t2 = std::move(t1);   // 移动构造
//
//    cout << "t1 joinable: " << t1.joinable() << endl;
//    cout << "t2 joinable: " << t2.joinable() << endl;
//
//    t2.join();
//
//    return 0;
//}


//void Print(size_t n, const string& s)
//{
//	for (size_t i = 0; i < n; i++)
//	{
//		cout << this_thread::get_id() << s << ":" << i << endl;
//	}
//}
//
//
//int main()
//{
//	size_t n;
//	cin >> n;
//
//	// 创建n个线程执行Print
//	vector<thread> vthd(n);
//	size_t j = 0;
//	for (auto& thd : vthd)
//	{
//		// 移动赋值
//		thd = thread(Print, 10, "线程" + to_string(j++));
//	}
//
//	for (auto& thd : vthd)
//	{
//		thd.join();
//	}
//
//	return 0;
//}





void Print()
{
    cout << "thread running" << endl;
}

//int main()
//{
//    // 1. 默认构造
//    thread t1;
//    cout << "t1 joinable: " << t1.joinable() << endl;
//
//    // 2. 正常创建线程
//    thread t2(Print);
//    cout << "t2 joinable: " << t2.joinable() << endl;
//
//    // 3. 移动后
//    thread t3 = std::move(t2);
//    cout << "t2 joinable after move: " << t2.joinable() << endl;
//    cout << "t3 joinable after move: " << t3.joinable() << endl;
//
//    // 4. join 之后
//    t3.join();
//    cout << "t3 joinable after join: " << t3.joinable() << endl;
//
//    // 5. detach 示例
//    thread t4(Print);
//    t4.detach();
//    cout << "t4 joinable after detach: " << t4.joinable() << endl;
//
//    return 0;
//}


//int main()
//{
//	int x = 0;
//	thread t1([&x]() { 
//		for (int i = 0; i < 5; i++)
//		{
//			x++;
//		}
//
//		cout << "x = " << x << endl;
//	});
//
//	thread t2([&x]() {
//		for (int i = 0; i < 5; i++)
//		{
//			x++;
//		}
//		cout << endl;
//		cout << "x = " << x << endl;
//	});
//
//	t1.join();
//	t2.join();
//
//	return 0;
//}



//void ThreadFunc1(int& x)
//{
//	x += 10;
//}
//
//void ThreadFunc2(int* x)
//{
//	*x += 10;
//}
//
//int main()
//{
//	int a = 10;
//
//	// 会报错
//	//thread t1(ThreadFunc1, a);
//	//t1.join();
//	cout << a << endl;
//
//	// 借助std::ref()函数
//	thread t2(ThreadFunc1, ref(a));
//	t2.join();
//	cout << a << endl;
//
//	// 地址的拷贝
//	thread t3(ThreadFunc2, &a);
//	t3.join();
//	cout << a << endl;
//
//	return 0;
//}

#include <mutex>

//unsigned long sum = 0L;
//std::mutex mtx;  // 定义一把锁
//
//void fun(size_t num)
//{
//	for (size_t i = 0; i < num; ++i)
//	{
//		mtx.lock();   // 加锁（进入临界区）
//		sum++;
//		mtx.unlock(); // 解锁（离开临界区）
//	}
//}
//
//int main()
//{
//	cout << "Before joining,sum = " << sum << std::endl;
//
//	thread t1(fun, 10000000);
//	thread t2(fun, 10000000);
//
//	t1.join();
//	t2.join();
//
//	cout << "After joining,sum = " << sum << std::endl;
//	return 0;
//}




#include <atomic>

////atomic_long sum{ 0 }; 这种写法也可以
//atomic<unsigned long> sum(0);  // 改成原子类型
//
//void fun(size_t num)
//{
//	for (size_t i = 0; i < num; ++i)
//		sum++;  // 原子操作（线程安全）
//}
//
//int main()
//{
//	cout << "Before joining,sum = " << sum << std::endl;
//
//	thread t1(fun, 10000000);
//	thread t2(fun, 10000000);
//
//	t1.join();
//	t2.join();
//
//	cout << "After joining,sum = " << sum << std::endl;
//	return 0;
//}



//int number = 0;
//mutex g_lock;
//
//int ThreadProc1()
//{
//	for (int i = 0; i < 100; i++)
//	{
//		std::lock_guard<std::mutex> lock(g_lock);
//
//		if (i == 50)
//			throw std::runtime_error("error");   // 自动释放锁
//
//		++number;
//		cout << "thread 1 :" << number << endl;
//	}
//	return 0;
//}
//
//int ThreadProc2()
//{
//	for (int i = 0; i < 100; i++)
//	{
//		g_lock.lock(); 
//		--number;
//		cout << "thread 2 :" << number << endl;
//		g_lock.unlock();
//	}
//	return 0;
//}
//
//
//
//int main()
//{
//	thread t1(ThreadProc1);
//	thread t2(ThreadProc2);
//
//	t1.join();
//	t2.join();
//
//	cout << "number:" << number << endl;
//
//	system("pause");
//	return 0;
//}





// 除0错误
void func()
{
	//srand(time(0));
	if (rand() % 2 == 0)
	{
		throw exception("异常");
	}
	else
	{
		cout << "func()" << endl;
	}
}

//int main()
//{
//	mutex mtx;
//	size_t n1 = 10000;
//	size_t n2 = 10000;
//
//	size_t x = 0;
//	srand(time(0));
//
//	thread t1([n1, &x, &mtx]() {
//		try
//		{
//			for (size_t i = 0; i < n1; i++)
//			{
//				// 延迟加锁
//				unique_lock<mutex> lock(mtx, defer_lock);
//
//				lock.lock();   // 手动加锁
//				++x;
//
//				func();        // 这里可能抛异常
//
//				lock.unlock(); // 手动解锁
//			}
//		}
//		catch (const exception& e)
//		{
//			cout << e.what() << endl;
//		}
//		});
//
//	thread t2([n2, &x, &mtx]() {
//		for (size_t i = 0; i < n2; i++)
//		{
//			unique_lock<mutex> lock(mtx); // 默认构造就加锁
//			++x;
//			// 这里不手动 unlock，也可以（析构自动释放）
//		}
//		});
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}



#include <condition_variable>

int main()
{
	mutex mtx;
	int x = 1;
	condition_variable cv;
	bool flag = false;

	// flag保证了t1先运行
	thread t1([&]() {
		for (int i = 0; i < 10; i++)
		{
			unique_lock<mutex> lock(mtx);
			if (flag)
			{
				cv.wait(lock);
			}

			cout << "thread 1[" << this_thread::get_id() << "] : " << x << endl;
			//cout << this_thread::get_id() << " : " << x << endl;
			++x;

			flag = true;
			cv.notify_one();
		}
	});

	thread t2([&mtx, &x, &cv, &flag]() {
		for (int i = 0; i < 10; i++)
		{
			unique_lock<mutex> lock(mtx); // 如果t1先抢到锁, 那么t2会被阻塞
			if (!flag)
			{
				cv.wait(lock);
			}

			cout << "thread 2[" << this_thread::get_id() << "] : " << x << endl;
			//cout << this_thread::get_id() << " : " << x << endl;
			++x;

			flag = false;
			cv.notify_one();
		}
	});

	t1.join();
	t2.join();

	return 0;
}