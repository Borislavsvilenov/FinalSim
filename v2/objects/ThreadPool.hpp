#pragma once
#include <thread>
#include <vector>

class ThreadPool {

public:
  std::vector<std::thread*> threads;

  ThreadPool();
  ~ThreadPool();

};
