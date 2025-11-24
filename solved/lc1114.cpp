#include <semaphore>
#include <thread>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Foo {
public:
    
    counting_semaphore<1> sem1 = counting_semaphore<1>(0);
    counting_semaphore<1> sem2 = counting_semaphore<1>(0);
    
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem1.release();
    }

    void second(function<void()> printSecond) {
        sem1.acquire();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem2.release();
    }

    void third(function<void()> printThird) {
        sem2.acquire();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

void helper(int i) {
    cout << "I am " << i << endl;
}

void f(Foo& foo, int id) {
    sleep(rand() % 2);
    if (id == 0) foo.first([&] () -> void {helper(0);});
    else if (id == 1) foo.second([&] () -> void {helper(1);});
    else foo.third([&] () -> void {helper(2);});
}

int main() {
    Foo foo;
    thread t1(f, ref(foo), 0);
    thread t2(f, ref(foo), 1);
    thread t3(f, ref(foo), 2);
    
    t3.join();
    t2.join();
    t1.join();
}

