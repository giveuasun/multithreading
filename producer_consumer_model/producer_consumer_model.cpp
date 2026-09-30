#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> tasks;          // 任务队列（共享数据）
mutex mtx;
condition_variable cv;
const int MAX_QUEUE = 5;

void producer(int id) {
    for (int i = 0; i < 5; i++) {
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [] { return tasks.size() < MAX_QUEUE; });  // 队列满了就等

            int task = id * 100 + i;
            tasks.push(task);
            cout << "生产者" << id << " 生产了任务: " << task << endl;
        }
        cv.notify_all();  // 通知消费者
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 5; i++) {
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [] { return !tasks.empty(); });  // 队列空了就等

            int task = tasks.front();
            tasks.pop();
            cout << "  消费者" << id << " 处理了任务: " << task << endl;
        }
        cv.notify_all();  // 通知生产者
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread p1(producer, 1);
    thread p2(producer, 2);
    thread c1(consumer, 1);
    thread c2(consumer, 2);

    p1.join(); p2.join();
    c1.join(); c2.join();

    cout << "全部完成！" << endl;
    return 0;
}

//这个例子用到的所有东西：
//
//thread → 创建线程
//mutex → 保护队列
//condition_variable → 队列满 / 空时等待
//queue → 共享数据
//atomic（可选）→ 如果加个 atomic<bool> done 控制退出
//
//跑起来你会看到生产者和消费者交替工作，队列永远不会满也不会空。