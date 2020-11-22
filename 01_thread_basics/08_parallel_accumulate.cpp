/* ************************************************************************
 * Created by    : Rahul Kumar Nonia
 * File name     : 08_parallel_accumulate.cpp
 * Created on    : Saturday 21 November 2020 05:42:58 PM IST
 * Last modified : Saturday 21 November 2020 05:44:22 PM IST
 * Description   : used accumulate algorithm on large number of data (vectors)
 * 				   divide data into chunks
 * 				   assign each thread a data chunk
 *				   return the result
 * ***********************************************************************/
	
#include <iostream>
#include <vector>    // vector
#include <thread>    // thread
#include <numeric>   // accumulate
#include <algorithm> // for_each
#include <utility>   // std::mem_fn

#define MIN_BLOCK_SIZE 1000   // chunck size

// this is function to calculate the result sequentially on large data set
void sequential_accumulate()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    // lamda expression
    auto dash_fold = [](std::string a, int b)
    {
        return std::move(a) + "-" + std::to_string(b);
    };

    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                            std::to_string(v[0]), dash_fold);

    std::cout << "sum = "  << sum << std::endl;
    std::cout << "product = "  << product << std::endl;
    std::cout << "dash fold = " << s << std::endl;
}

template <typename iterator, typename T>
T accumulate(iterator start, iterator end, T &ref)
{
    ref = std::accumulate(start, end, 0);
}

// parallel accumulation
// data will be divided in chunks
// result of each chunk will be calculated in specific thread
template <typename iterator, typename T>

T parallel_accumulate(iterator start, iterator end, T &ref)
{
    int input_size = std::distance(start, end);

    int allowed_threads_by_elements = input_size / MIN_BLOCK_SIZE;  
    int allowed_threads_by_hardware = std::thread::hardware_concurrency();


    // number of threads to be spawned
    int num_threads = std::min(allowed_threads_by_elements, allowed_threads_by_hardware);

    // resizing block
    int data_block_size = (input_size + 1) / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1); 

    iterator last; // last element of each data block
    
    for(int i = 0; i < num_threads - 1; i++){
        last = start;
        std::advance(last, data_block_size); // advance last by block size
        threads[i] = std::thread(accumulate<iterator, T>, start, last, std::ref(results[i]));
        start = last;
    }
    std::advance(last, data_block_size);

    results[num_threads - 1] = std::accumulate(start, last, 0);

    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    for(auto i = 0; i < num_threads - 1; i++){
        try{
        if(threads[i].joinable()){
            threads[i].join();
        }
        }
        catch(...){
            printf("Exception for: %d\n", i);
        }
    }


    return std::accumulate(results.begin(), results.end(), ref);
}

int main()
{
    //sequential_accumulate();

    const int size = 8000;
    
    int *my_array = new int[size];
    int ref = 0;

    for(auto i = 0; i < size; i++){
        my_array[i] = rand() % 15;
    }

    int result  = std::accumulate(my_array, my_array+size, 0);

    std::cout << "sequential result " << result << std::endl;
   

    int ret_val = parallel_accumulate<int*, int>(my_array, my_array+size, ref);
    std::cout << "result = " << ret_val << std::endl;

    return 0;
}