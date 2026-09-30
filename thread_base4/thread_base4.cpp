#include <iostream>
#include <thread>
using namespace std;

int main() {
    int x = 10;

    thread t([x]() {           // lambda作为线程函数
        cout << "x = " << x << endl;
        });

    t.join();
    return 0;
}

//Lambda写线程函数很方便，不用单独定义一个函数。你以后会经常看到这种写法。