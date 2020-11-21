#include  <iostream>
#include <thread>

void work()
{
    printf("this is worker thread\n");
}

void other_operation()
{
    printf("this is other operation\n");
    throw std::runtime_error("This is runtime_error is thrown intentionally\n");
}

// 4th step 
// better solution
// RAII (resource acquisition is initialisation)
class thread_guard{
    std::thread &t;

    public:
        explicit thread_guard(std::thread &_t) : t(_t)
        {}

        ~thread_guard()
        {
            if(t.joinable()){
                t.join();
            }
        }

        // delete copy constructor and assignment operator
        thread_guard(thread_guard &) = delete;
        thread_guard & operator=(thread_guard & ) = delete;
};

int main()
{
    std::thread thread1(work);
    thread_guard tg_thread(thread1); // 4th step
    //other_operation();
    // throw an exception and thread  will not join
    //thread1.join();  -> 1

    // solution put in try catch block
    // try{
    //     other_operation(); // throws exception and falls to catch block
    //     thread1.join();    // this will not execute, put this also in catch block -> 2
    // }
    // catch(...)
    // {
    //     printf("this is catch block\n");
    //     thread1.join();   // now program runs without error -> 3
    // }

    // 4th step
    // now this works
    try {
        other_operation();

    }
    catch(...){

    }

    return 0;
}