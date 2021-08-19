#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include <cstdlib>
using namespace std;


class Test{
public:
    void ThreadPush() {
        int num = 0;
        while(1){
            chrono::milliseconds t(100);
            this_thread::sleep_for(t);
            unique_lock<mutex> lock1(m_mutex);
            m_queue.push(num = rand()%100);
            lock1.unlock();
            cout << "push num :" << num << " successful" << endl;
            cout << "notify all thread...." << endl;
            m_cond.notify_all();
        }
    }
    void ThreadPop() {
        while(1) {
            chrono::milliseconds t(1000);
            this_thread::sleep_for(t);
            unique_lock<mutex> lock1(m_mutex);
            m_cond.wait(lock1, [&] { return !m_queue.empty(); });
            cout << "threadid: " << this_thread::get_id() << " obtain num: " << m_queue.front() << endl;
            m_queue.pop();
        }
    }

private:
    static queue<int> m_queue;
    static mutex m_mutex;
    static condition_variable m_cond;
};
condition_variable Test::m_cond;
mutex Test::m_mutex;
queue<int> Test::m_queue;

int main() {
    srand((int)time(nullptr)); 
    vector<thread> vec;
    Test t;
    Test t2;
    thread t1(&Test::ThreadPush, &t);
    for (int i = 0; i < 5;++i) {
        vec.emplace_back(&Test::ThreadPop, &t2);
    }
    for(auto &thread:vec) {
        thread.join();
    }
    t1.join();
    return 0;
}