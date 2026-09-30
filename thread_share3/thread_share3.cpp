#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int total = 0;
mutex mtx;

void addNumbers() {
    for (int i = 0; i < 500; i++) {
        {
            lock_guard<mutex> lock(mtx);  // 创建时自动上锁
            total++;
            cout << "total = " << total << endl;
        }  // 出了这个花括号，lock销毁，自动解锁
    }
}

int main() {
    thread t1(addNumbers);
    thread t2(addNumbers);

    t1.join();
    t2.join();

    cout << "最终结果: " << total << endl;
    return 0;
}

//为什么用lock_guard更好：
//
//不用手动unlock，不会忘记
//如果代码抛异常了，它也会自动解锁，不会死锁