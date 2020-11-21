#include <iostream>
#include <thread>
#include <chrono>


// what happens when variable goes out of 
// scope while thread is still running

void work2(int &x)
{
    printf("this is worker thread 2\n");
    while(true){
        try{
        printf("Value of x in worker thread 2: %d\n", x);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        catch(...){
            throw std::runtime_error("This is throw intentionally");
        }
    }
}

void work1()
{
    int x = 100;
    printf("this is worker thread\n");

    std::thread thread2(work2, std::ref(x));
    thread2.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread 1 executed\n";
}

int main()
{
    std::thread thread1(work1);
    thread1.join();
    return 0;
}