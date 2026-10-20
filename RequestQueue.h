/**
 * @file RequestQueue.h
 * @brief Declares RequestQueue, a FIFO queue of requests.
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @class RequestQueue
 * @brief First-in, first-out line of requests waiting for a server.
 *
 * The LoadBalancer pushes accepted requests onto the back and hands
 * requests from the front to idle WebServers. Its size drives the
 * server scaling decision.
 */
class RequestQueue {
public:
    /**
     * @brief Adds a request to the back of the queue.
     * @param r Request to add.
     */
    void push(const Request& r);

    /**
     * @brief Removes and returns the request at the front.
     * @pre The queue is not empty.
     * @return The oldest waiting request.
     */
    Request pop();

    /**
     * @brief Number of waiting requests.
     * @return Current queue size.
     */
    int size() const;

    /**
     * @brief Whether the queue has no requests.
     * @return true if empty.
     */
    bool empty() const;

private:
    std::queue<Request> q; ///< Underlying standard library queue.
};

#endif
