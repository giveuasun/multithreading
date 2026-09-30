#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int total = 0;
mutex mtx;  // 创建一个互斥锁

void addNumbers() {
    for (int i = 0; i < 500; i++) {
        mtx.lock();      // 上锁：我要改total了，别人别动
        total++;
        cout << "total = " << total << endl;
        mtx.unlock();    // 解锁：我改完了，别人可以动了
    }
}

int main() {
    thread t1(addNumbers);
    thread t2(addNumbers);

    t1.join();
    t2.join();

    cout << "最终结果: " << total << endl;  // 这次一定是10 ✅
    return 0;
}