#include <semaphore>
#include <iostream>
#include <vector>
#include <functional>
#include <semaphore.h>
#include <thread>
#include <unistd.h>
#include <omp.h>
using namespace std;

#define SZ 999

// 4 philosphers will not result in deadlock, so use a semaphore to ensure only 4 threads enter
// the eating part

// I dont know why I get WA, test on local computer is correct, so I just made sure only 1 thread
// can enter the table

class DiningPhilosophers {
public:
    sem_t leftForks[5];
    sem_t rightForks[5];
    sem_t sem;


    DiningPhilosophers() {
        for (int i = 0; i < 5; i ++) {
            sem_init(leftForks + i, 0, 1);
            sem_init(rightForks + i, 0, 1);
        }
        sem_init(&sem, 0, 4);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        sem_wait(&sem);
        
        sem_wait(rightForks + philosopher);
        pickRightFork();
        
        sem_wait(leftForks + ((philosopher + 1) % 5));
        pickLeftFork();
        
        eat();

        putLeftFork();
        sem_post(leftForks + ((philosopher + 1) % 5));

        putRightFork();
        sem_post(rightForks + philosopher);

        sem_post(&sem);
		
    }
};

void f(int id, int fork, int action) {
    printf("[%d %d %d]\n", id, fork, action);
}

int main() {
    DiningPhilosophers din;
    vector<thread> arr;
    for (int i = 0; i < 5; i ++) {
        arr.emplace_back([&din, i] () -> void {
            for (int j = 0; j < 2; j ++) {
                sleep(rand() % 2);
                din.wantsToEat(i,
                    [&] () -> void {f(i, 1, 1);},
                    [&] () -> void {f(i, 2, 1);},
                    [&] () -> void {f(i, 0, 3);},
                    [&] () -> void {f(i, 1, 2);},
                    [&] () -> void {f(i, 2, 2);}
                );
            }
            
            
        ;});
        
    }

    #pragma omp parallel for
    for (int i = 0; i < 5; i ++) {
        arr[i].join();
    }

    
}   