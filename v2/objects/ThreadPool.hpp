#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {

public:
  std::vector<std::thread*> threads;
  std::queue<std::function<void()>> queue;
  std::mutex Mutex;
  std::condition_variable condition; 

  bool stop;

  ThreadPool();
  ~ThreadPool();

  void createNewThread();
  void removeThread();

  template<class F>
  void addToQ(F&& task);

  template<class F>
  void execute(F&& task);


};
