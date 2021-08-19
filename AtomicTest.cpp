#include<iostream>
#include<thread>
#include<chrono>
#include<atomic>
#include<mutex>
using namespace std;
atomic_int num(0);
volatile int num2 = 0;
mutex Mutex;
void ThreadA() {
    for (int i = 0; i < 10000000;++i) {
        //++num;
        ++num2;
    }
}

int main() {
    thread t1(ThreadA), t2(ThreadA);
    t1.join();
    t2.join();
    cout << "final the num is: " << num << endl;
    cout << "final the num is: " << num2 << endl;
    return 0;
}