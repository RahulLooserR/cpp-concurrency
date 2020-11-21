#include <iostream>
#include <thread>

// taking owner of other thread
// ownership can be transferred only to the default thread constructor
// not to the thread owning other thread.

void worker1()
{
    printf("thread function 1: %d\n", std::this_thread::get_id());
    std::cout << "thread function 1: " << std::this_thread::get_id() << std::endl;
}

void worker2()
{
    printf("thread function 1: %d\n", std::this_thread::get_id());
    std::cout << "thread function 1: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread thread1(worker1);

    // std::thread thread2 = thread1;   copy assignment not allowed
    std::thread thread2 = std::move(thread1);  // changing ownership before join

    // now thread1 does not own anything
    thread1 = std::thread(worker2);      // move is used

    std::thread thread3(worker1);
    //thread3 = std::move(thread1);  // not allowed since thread1 is owning a thread

    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}