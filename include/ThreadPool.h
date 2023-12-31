/*
* this ThreadPool implementation is from https://github.com/progschj/ThreadPool
* another version with Chinese comment: https://github.com/Camio1945/ThreadPool
*/
#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
 
// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(   // lambda function for what each thread should do once created
            [this]
            {
                while(true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,  // wake up as long as there is task in the queue
                            [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());  // std::move() is used to avoid copying
                        this->tasks.pop();
                    }

                    task(); // task execution
                }
            }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) // variadic template
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    /*
    *   std::bind returns a callable object
    *   std::forward avoids copying
    *   <Args>(args)... is used to expand the parameter pack
    *   std::packaged_task wraps a callable object so that it can be invoked asynchronously. returns return_type
    *   std::make_shared returns a shared_ptr(smart pointer) which points to a callable object in std::packaged_task<return_type()>
    */
    auto task = std::make_shared< std::packaged_task<return_type()> >(  // a reason to use packaged_task is to obtain the result by get_fucture()
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one(); // notify one of the thread that there is a task available
    return res; 
    // res is a std::future object. we can call res.get() to get the result
    // res.get() will block until the result is ready
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;    // set stop flag to true
    }
    condition.notify_all(); // notify all threads that stop flag is set to true
    for(std::thread &worker: workers)
        worker.join();  // join all threads
}
