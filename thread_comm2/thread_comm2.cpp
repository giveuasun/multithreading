#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void worker() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });  // 等ready变成true才继续
    cout << "开始工作！" << endl;
}

int main() {
    thread t(worker);

    // 模拟做点准备工作
    this_thread::sleep_for(chrono::seconds(1));

    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();  // 通知worker：可以开始了

    t.join();
}

//条件变量做的事：
//
//worker线程调用 cv.wait() → 自动解锁并休眠，不浪费CPU
//main线程设置ready = true，调用 cv.notify_one() → worker被唤醒，重新加锁，检查条件，继续运行