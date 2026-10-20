/**
 * @file RequestQueue.cpp
 * @brief Implements RequestQueue.
 */

#include "RequestQueue.h"

void RequestQueue::push(const Request& r) {
    q.push(r);
}

Request RequestQueue::pop() {
    Request front = q.front();
    q.pop();
    return front;
}

int RequestQueue::size() const {
    return static_cast<int>(q.size());
}

bool RequestQueue::empty() const {
    return q.empty();
}
