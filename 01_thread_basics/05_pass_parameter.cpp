#include <iostream>
#include <thread>

void work1(int a, int b)
{
    printf("this is worker thread 1, a + b = %d \n", a+b);
}

void work2(int &x)
{
    printf("this is worker thread 2\n");
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("value of x = %d\n", x);
    }
}

int main()
{
    int a = 10, b = 9;
    std::thread thread1(work1, a, b);

    // by default thread does not support reference
    // use std::ref() for passing reference
    std::thread thread2(work2, std::ref(a));
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    a =  100;

    thread1.join();
    thread2.join();
    return 0;
}