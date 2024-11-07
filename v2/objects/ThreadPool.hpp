#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
  public:
    ThreadPool(size_t numThreads);

    template<class F, class... Args>
      auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using return_type = decltype(f(args...));

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();

        {
          std::unique_lock<std::mutex> lock(queueMutex);

          if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

          tasks.emplace([task]() { (*task)(); });
        }

        condition.notify_one();

        return res;
      }

    ~ThreadPool();

  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};
