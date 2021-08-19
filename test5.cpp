#include<thread>
#include <iostream>
#include<chrono>
#include<atomic>
#include <future>
#include<mutex>
using namespace std;
atomic_int num(0);
volatile int num2 = 0;
mutex Mutex;
void ThreadA() {
    for (int i = 0; i < 10000000;++i) {
        ++num;
        ++num2;

    }
}
class A{
public:
    int ThreadA(int a) {
        this_thread::sleep_for(chrono::milliseconds(5000));
        a *= 200;
        a +=5;
        cout<<"threadID:"<<this_thread::get_id()<<" process result is "<<a<<endl;
        res1.set_value(a);
        return a;

    }
    void ThreadB() {
        cout<<"waiting front thread1 data......"<<endl;
        int a = res1.get_future().get();
        cout<<"threadID:"<<this_thread::get_id()<<" get data "<<a<<" will begin process it"<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        a *= 100;
        cout<<"threadID:"<<this_thread::get_id()<<" will process result is "<<a<<endl;
        res2.set_value(a);

    }
    void ThreadC() {
        cout<<"waiting front thread2 data......"<<endl;
        int a = res2.get_future().get();
        cout<<"threadID:"<<this_thread::get_id()<<" get data "<<a<<" will begin process it"<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        a *= 100;
        cout<<"threadID:"<<this_thread::get_id()<<" will process result is "<<a<<endl;
        res3.set_value(a);

    }
    int getValue() { return res3.get_future().get(); }

private:
    static promise<int> res1;
    static promise<int> res2;
    static promise<int> res3;
}; 
promise<int> A::res1;
promise<int> A::res2;
promise<int> A::res3;

int main() {
    //promise<int> tr,tr2,tr3;
    //future<int> final1 = tr3.get_future();
//    thread t1(ThreadA), t2(ThreadA);
//    t1.join();
//    t2.join();
    A a,b,c;
    thread t3(&A::ThreadA,&a,10);
    thread t4(&A::ThreadB,&b);
    thread t5(&A::ThreadC,&c);
    t3.join();
    t4.join();
    t5.join();
//    cout << "final the num is: " << num << endl;
//    cout << "final the num is: " << num2 << endl;
    cout<<"final num is "<<a.getValue()<<endl;
    return 0;
}