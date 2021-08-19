#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<future>
#include<condition_variable>
using namespace std;

volatile bool flag = false;

class A {
public:
    A() {}
    void threadA() {
        cout << "threadA begin...." << endl;
        unique_lock<mutex> lock1(m_mutex);
        cout << "waiting...." << endl;
        cond.wait(lock1, [] { return flag == true; });
        cout << "被唤醒:" << flag << endl;
    }

    void threadB() {

        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "threadB begin...." << endl;
        cond.notify_one();
        cout << "first notify...." << endl;
        
        unique_lock<mutex> lock1(m_mutex);
        flag = true;
        lock1.unlock();

        cond.notify_one();
        cout << "sencond notify...." << endl;
    }

    int myAsync(int &num) {
        chrono::milliseconds time(5000);
        ++num;
        num *= 100;
        this_thread::sleep_for(time);
        return num;
    }
private:
    condition_variable cond;
    mutex m_mutex;
};


int main() {
    A a;
    int num = 10;
    thread t1(&A::threadA, ref(a));
    thread t2(&A::threadB, ref(a));
    future<int> res = async(launch::async, &A::myAsync,&a,ref(num));
    t1.join();
    t2.join();
    cout << res.get() << endl;
    cout << num << endl;
    return 0;
}