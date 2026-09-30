#include <iostream>
#include <thread>
using namespace std;

void countNumbers(int start, int end) {
    for (int i = start; i < end; i++) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    thread t1(countNumbers, 0, 50);
    thread t2(countNumbers, 100, 150);

    t1.join();
    t2.join();

    cout << "两个线程都跑完了" << endl;
    return 0;
}

//两个线程同时跑
//注意：两个线程的输出是"混在一起"的，因为它们同时往屏幕写东西。这是正常的，不是bug。