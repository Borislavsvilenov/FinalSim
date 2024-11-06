#include "ThreadPool.hpp"

ThreadPool::ThreadPool () : stop(false) {

}

ThreadPool::~ThreadPool () {

}

void ThreadPool::createNewThread() {
  
}

void ThreadPool::removeThread() {

}

template<class F>
void ThreadPool::addToQ(F&& task) {
  queue.emplace(task);
}

template<class F>
void ThreadPool::execute(F&& task) {

  return;
}
