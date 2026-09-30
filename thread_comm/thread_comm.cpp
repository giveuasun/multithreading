#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<bool> ready(false);

void worker() {
    while (!ready) {  // 不停地检查
        // 空转，浪费CPU
    }
    cout << "开始工作！" << endl;
}

int main() {
    thread t(worker);
    // 做点别的...
    ready = true;  // 通知worker可以开始了
    t.join();
}

//为什么需要条件变量？
//
//有时候一个线程需要等另一个线程"干完某件事"才能继续。比如：
//
//生产者生产了数据，消费者才能处理
//初始化完成，工作线程才能开始

//问题：​ worker线程在 while (!ready) 里疯狂空转，CPU占用100% 。