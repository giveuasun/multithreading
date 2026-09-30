#include <iostream>
#include <thread>
using namespace std;

void printId(int id, const string& name) {
    cout << "id = " << id << ", name = " << name << endl;
}

int main() {
    thread t(printId, 1, "worker");
    t.join();
    thread t2(printId, 2, "worker2");
    t2.join();
    return 0;
}

// 传参给多线程

// 创建线程时，函数名后面的参数就是传给那个函数的参数，按顺序对应。