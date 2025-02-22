#include <semaphore>
#include <thread>
#include <barrier>
#include <bits/stdc++.h>
using namespace std;

// remember to compile with -std=c++20

class H2O {
    barrier<function<void()>> b = barrier<function<void()>>(3, []() -> void {});
    counting_semaphore<999> semH = counting_semaphore<999>(2);
    counting_semaphore<999> semO = counting_semaphore<999>(1);
public:
    H2O() {
        
    }

    

    void hydrogen(function<void()> releaseHydrogen) {
        semH.acquire();
        b.arrive_and_wait();
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        // have to put this inside semH, if outside of semH, will have error
        // suppose 2 sets go through the barrier, without having called releaseH/ releaseO
        //, then the order of which releaseH() and releaseO() is called
        // is not known
        releaseHydrogen();
        semH.release();
        
    }

    void oxygen(function<void()> releaseOxygen) {
        semO.acquire();
        b.arrive_and_wait();
       
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        semO.release();
    }
};

int main() {
    binary_semaphore lock(1);
    H2O h2o;
    string str = "OHOHOOHHOHHOOHHHHOOHOOHHOHHOOHHHOOHOHHOHHOHHHHHOHHHHHHHHHHHH";
    vector<thread> arr;
    for (int i = 0; i < str.size(); i ++) {
        if (str[i] == 'H') arr.push_back(thread([&] () -> void {h2o.hydrogen([&]() -> void {
            lock.acquire();
            cout << "H" << endl;
            lock.release();
        });}));
        else arr.push_back(thread([&]() -> void {h2o.oxygen([&]() -> void {
            lock.acquire();
            cout << "O" << endl;
            lock.release();
        });}));
    }

    for (thread& t : arr) {
        t.join();
    }
}