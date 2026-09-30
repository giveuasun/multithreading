#include <iostream>
#include <thread>
using namespace std;

void hello() {
    cout << "你好，我是线程！" << endl;
}

int main() {
    thread t(hello);   // 创建一个线程，去执行 hello()
    t.join();          // 等线程跑完
    cout << "线程结束了" << endl;
    return 0;
}

//thread t(hello) → 创建了一个新线程，它去执行 hello() 函数
//
//t.join() → main函数在这里"卡住"，等hello线程跑完才继续
//
//如果不写 join()，main函数可能在线程没跑完时就结束了，程序会崩溃
//
//📌 记住：每个thread都必须要么join()，要么detach()，不能不管。