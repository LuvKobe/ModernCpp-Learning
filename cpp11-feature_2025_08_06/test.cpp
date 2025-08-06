#include "Thread.hpp"
#include <memory>

// 共享资源 --- 火车票
int tickets = 10000;

// 尽可能的让多个线程交叉执行
// 多个线程交叉执行的本质：就是让调度器尽可能的频繁发生线程调度与切换
// 线程一般在什么时候发生切换呢？时间片到了, 来了更高优先级的线程
// 线程是在什么检测到上面的问题呢？从内核态返回用户态的时候, 线程要对调度状态进行检测, 如果可以, 就直接发生线程切换

void *getTicket(void* args)
{
    //sleep(1);
    string username = static_cast<char*>(args);
    while (true)
    {
        if (tickets > 0)
        {
            // 休眠的这段的时间模拟真实的抢票花费的时间
            usleep(1254); // 1s = 1000ms = 1000 000ws
            // 开始抢
            cout << username << " 正在进行抢票: " << tickets << endl;
            tickets--;
        }
        else
        {
            // 没票的话直接退出
            break;
        }
    }
    return nullptr;
}

int main()
{
    /*
    std::unique_ptr 是 C++11 引入的智能指针类型，用来 独占式地管理动态内存。
    它能自动释放资源，避免内存泄漏，是裸指针 new/delete 的现代替代品。
    */
    unique_ptr<Thread> thread1(new Thread(getTicket, (void*)"user 1", 1));
    unique_ptr<Thread> thread2(new Thread(getTicket, (void*)"user 2", 2));
    unique_ptr<Thread> thread3(new Thread(getTicket, (void*)"user 3", 3));
    unique_ptr<Thread> thread4(new Thread(getTicket, (void*)"user 4", 4));

    
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();

    thread1->join();
    thread2->join();
    thread3->join();
    thread4->join();

    return 0;
}

