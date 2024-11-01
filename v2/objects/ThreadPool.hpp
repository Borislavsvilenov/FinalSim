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

  ThreadPool();
  ~ThreadPool();

  void createNewThread();
  void removeThread();

  void addToQ(std::function<void()>);


};
