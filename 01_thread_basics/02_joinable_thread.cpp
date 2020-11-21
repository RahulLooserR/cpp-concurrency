#include <iostream>
#include <thread>

void work()
{
    printf("this is work thread\n");
}

int main()
{
    std::thread thread1(work);

    if(thread1.joinable()){
        printf("Thread is joinable\n");
    }
    else{
        printf("Thread is not joinable\n");
    }

    // always check for joinability of thread 
    thread1.join();

    if(thread1.joinable()){
        printf("Thread is joinable\n");
    }
    else{
        printf("Thread is not joinable\n");
    }

    // default constructor is non joinable
    std::thread thread2;
    if(thread2.joinable()){
        printf("Thread is joinable\n");
    }
    else{
        printf("Thread is not joinable\n");
    }

    return 0;
}