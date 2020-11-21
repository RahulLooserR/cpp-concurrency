#include <iostream>
#include <thread>

void threadFunc1()
{
    printf("thread function 1: %d\n", std::this_thread::get_id());
    std::cout << "thread function 1: " << std::this_thread::get_id() << std::endl;
}

class callable_class{
    public:
    // overload operator () multiple arguments
        void operator()(){
            printf("from class with function call operator: %d\n", std::this_thread::get_id());
        }
};

int main()
{
    // creating thread from function
    std::thread thread1(threadFunc1);

    callable_class obj;
    // creating thread from callable object
    // must overload operator ()
    std::thread thread2(obj);   

    // creating thread from lambda expression 
    std::thread thread3([]
    {
        printf("from lambda: %d\n", std::this_thread::get_id());
    });

    printf("from main: %d\n", std::this_thread::get_id());
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}