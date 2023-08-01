#ifndef QUEUE_H
#define QUEUE_H
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

class Queue {
    mutable std::mutex m;
    std::condition_variable cv;
    std::queue<std::string> q;

public:
    void push(std::string s);
    std::string pop();
    Queue() = default;
    ~Queue() = default;
};

#endif // !QUEUE_H