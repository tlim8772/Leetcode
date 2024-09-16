#include <semaphore>
#include <functional>
#include <thread>
#include <iostream>
using namespace std;

// busy waiting, could make it better, but will need more semaphores
// just wanted to see if busy waiting works, but this solution may result in starvation

class ZeroEvenOdd {
private:
    int n;
    int cnt = 0;
    counting_semaphore<999> sem{1};

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i ++) {
            bool printed = false;
            while (true) {
                sem.acquire();
                if (cnt % 2 == 0) {
                    printed = true;
                    cnt ++;
                    printNumber(0);
                }
                sem.release();
                if (printed) break;
            }
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            bool printed = false;
            while (true) {
                sem.acquire();
                if (cnt >= 1 && (cnt - 1) % 4 == 0) {
                    printed = true;
                    cnt ++;
                    printNumber(i);
                }
                sem.release();
                if (printed) break;
            }
        }
    }

    void even(function<void(int)> printNumber) {
         for (int i = 2; i <= n; i += 2) {
            bool printed = false;
            while (true) {
                sem.acquire();
                if (cnt >= 3 && (cnt - 3) % 4 == 0) {
                    printed = true;
                    cnt ++;
                    printNumber(i);
                }
                sem.release();
                if (printed) break;
            }
        }
    }
};

void f(int i) {
    cout << i << endl;
}

int main() {
    ZeroEvenOdd zeo(7);

    thread t0([&]() -> void {zeo.zero(f);});
    thread t1([&]() -> void {zeo.odd(f);});
    thread t2([&]() -> void {zeo.even(f);});

    t0.join();
    t1.join();
    t2.join();
}