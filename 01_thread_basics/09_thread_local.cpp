#include <iostream>
#include <thread>

std::atomic<int> i = 0;

void work()
{
    ++i;
    std::cout << i << std::endl;
}

int main()
{

    return 0;
}