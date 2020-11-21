#include <iostream>
#include <thread>
#include <chrono> // sleep 

void work()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    printf("this is work thread\n");
}

void work1()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    printf("this is work1 thread\n");
}

int main()
{
    std::thread thread1(work);
    std::thread thread2(work1);

    thread2.detach();
    printf("thread2 detached\n");

    thread1.join();
    printf("thread1 joined\n");

    return 0;
}