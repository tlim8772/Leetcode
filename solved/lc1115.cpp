#include <semaphore>
#include <thread>
#include <bits/stdc++.h>
using namespace std;

class FooBar {
private:
    int n;
    counting_semaphore<999> sem0;
    counting_semaphore<999> sem1;

public:
    FooBar(int n): sem0(1), sem1(0) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            sem0.acquire();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            sem1.release();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            sem1.acquire();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            sem0.release();
        }
    }
};

int main() {
    FooBar foobar(10);
    thread t0([&]() -> void {foobar.foo([]() -> void {printf("foo\n");});});
    thread t1([&]() -> void {foobar.bar([]() -> void {printf("bar\n");});});
    t1.join();
    t0.join();


}