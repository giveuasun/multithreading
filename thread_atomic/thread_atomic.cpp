#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> total(0);  // 把int换成atomic<int>

void addNumbers() {
    for (int i = 0; i < 500; i++) {
        total++;  // 不用加锁！天生安全
        cout << "total = " << total << endl;
    }
}

int main() {
    thread t1(addNumbers);
    thread t2(addNumbers);

    t1.join();
    t2.join();

    cout << "最终结果: " << total << endl;  // 一定是10 ✅
    return 0;
}
