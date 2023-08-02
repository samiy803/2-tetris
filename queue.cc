#include "queue.h"

using namespace std;

void Queue::push(string s)
{
    lock_guard<mutex> lck(m);
    q.push(s);
    cv.notify_one();
}

string Queue::pop()
{
    unique_lock<mutex> lck(m);
    while (q.empty()) {
        cv.wait(lck);
    }
    string s = q.front();
    q.pop();
    return s;
}
