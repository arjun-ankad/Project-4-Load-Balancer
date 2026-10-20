/**
 * @file WebServer.h
 * @brief Declares WebServer, which processes one request at a time.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief A single server that takes a request, works on it one clock cycle
 *        at a time, and becomes idle when the request is finished.
 */
class WebServer {
public:
    /**
     * @brief Creates an idle server.
     * @param id Unique server number, used in logs.
     */
    explicit WebServer(int id);

    /**
     * @brief Starts working on a request.
     * @pre The server is idle.
     * @param r Request to process; its time becomes the remaining work.
     */
    void assign(const Request& r);

    /**
     * @brief Performs one clock cycle of work.
     * @return true on the cycle the current request finishes, otherwise false.
     *         Always false when idle.
     */
    bool tick();

    /**
     * @brief Whether the server has no request.
     * @return true if idle and ready for another request.
     */
    bool isIdle() const;

    /** @return This server's id. */
    int getId() const;

    /** @return Number of requests this server has finished. */
    int getCompleted() const;

    /** @return The request being processed (meaningful only when busy). */
    const Request& getCurrent() const;

private:
    int id;             ///< Server number.
    Request current;    ///< Request being processed.
    int timeLeft = 0;   ///< Clock cycles left on the current request.
    bool busy = false;  ///< true while a request is assigned.
    int completed = 0;  ///< Requests finished so far.
};

#endif
