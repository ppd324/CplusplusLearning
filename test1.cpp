#include<iostream>
#include<thread>
using namespace std;

class A{
public:
    A(int a = 0) : m_a(a) { cout << "constructor Is Called" << this<<endl; }
    A(const A &a):m_a(a.m_a){cout << "Copy constructor is called" <<this<< endl; }
    A(const A &&a):m_a(a.m_a){cout << "Mobile copy constructor is called" << this<<endl; }
    ~A(){cout << "析构函数被调用" << this<<endl; }
    int get()const { return m_a; }

private:
    int m_a;
};

void myTest(const int &i,const A &a) {
    cout << i << " :地址为" << &i << endl;
    cout << "a的member is:" << a.get() << " a的地址为" << &a << endl;
}
int main(){
    int i = 0;
    cout << "main:addr" << &i << endl;
    A a(5);
    //thread mytest1(myTest,ref(i),a);  //调用拷贝构造函数
    thread mytest1(myTest,i,ref(a)); //调用移动拷贝构造函数
    mytest1.join();
    cout << "hello,world\n";
    {
        int num = 0;
        thread mytest2([&num](int x, int y) {
            ++num;
            cout << num << endl;
            cout << num * x * y << endl;
        },10, 20);
        mytest2.join();
        cout << num << endl;
    }
}