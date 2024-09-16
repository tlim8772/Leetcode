#include <semaphore.h>
#include <bits/stdc++.h>
#include <thread>
using namespace std;

// we use semaphores to order the threads calling of printFizz, printBuzz etc

class FizzBuzz {
private:
    int n;
    int cnt = 1;
    sem_t sems[4];

public:
    FizzBuzz(int n) {
        this->n = n;
        for (int i = 0; i < 4; i ++) {
            sem_init(sems + i, 0, 0);
        }
        sem_post(sems + 3);
        
    }

    int which_sem(int i) {
        if ( i % 3 == 0 && i % 5 == 0) {
            return 2;
        } else if (i % 3 == 0) {
            return 0;
        } else if (i % 5 == 0) {
            return 1;
        } else {
            return 3;
        }
    }

    void process(int idx, function<void()> print) {
        sem_wait(sems + idx);
        print();
        cnt ++;
        sem_post(sems + which_sem(cnt));
    }

    void done() {
        for (int i = 0; i < 4; i ++) {
            sem_post(sems + i);
        }
    }

    // printFizz() outputs "fizz". sems[0]
    void fizz(function<void()> printFizz) {
        while (true) {
            sem_wait(sems);
            
            if (cnt <= n) {
                cnt ++;
                printFizz();
            } else {
                break;
            }

            if (cnt > n) done();
            sem_post(sems + which_sem(cnt));
        }
    }

    // printBuzz() outputs "buzz". sems[1]
    void buzz(function<void()> printBuzz) {
        while (true) {
            sem_wait(sems + 1);
            
            if (cnt <= n) {
                cnt ++;
                printBuzz();
            } else {
                break;
            } 

            if (cnt > n) done();
            sem_post(sems + which_sem(cnt));
        }

    }

    // printFizzBuzz() outputs "fizzbuzz". sems[2]
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            sem_wait(sems + 2);
            
            if (cnt <= n) {
                cnt ++;
                printFizzBuzz();
            } else {
                break;
            }

            if (cnt > n) done();
            sem_post(sems + which_sem(cnt));
        }
    }

    // printNumber(x) outputs "x", where x is an integer. sems[3]
    void number(function<void(int)> printNumber) {
        while (true) {
            sem_wait(sems + 3);
            
            if (cnt <= n) {
                cnt ++;
                printNumber(cnt - 1);
            } else {
                break;
            }

            if (cnt > n) done();
            sem_post(sems + which_sem(cnt));

            
        }
    }
};

void printFizz() {
    cout << "fizz" << endl;
}

void printBuzz() {
    cout << "buzz" << endl;
}

void printFizzBuzz() {
    cout << "fizzbuzz" << endl;
}

void printNumber(int i) {
    cout << i << endl;
}

int main() {
    FizzBuzz fb(15);
    thread t0([&]() -> void {fb.fizz(printFizz);});
    thread t1([&]() -> void {fb.buzz(printBuzz);});
    thread t2([&]() -> void {fb.fizzbuzz(printFizzBuzz);});
    thread t3([&]() -> void {fb.number(printNumber);});

    t0.join(); t1.join(); t2.join(); t3.join();
}