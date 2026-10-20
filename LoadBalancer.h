/**
 * @file LoadBalancer.h
 * @brief Declares LoadBalancer, which manages the request queue and web servers.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <ostream>
#include <string>
#include <vector>

#include "Config.h"
#include "IPBlocker.h"
#include "Logger.h"
#include "RequestQueue.h"
#include "Stats.h"
#include "WebServer.h"

/**
 * @class LoadBalancer
 * @brief Owns a request queue and a pool of web servers, keeps the clock,
 *        hands requests to idle servers, and adds or removes servers to keep
 *        the queue between 50 and 80 requests per server.
 *
 * Every LoadBalancer holds all of its own state, so several can run at once
 * (used by the bonus Switch).
 */
class LoadBalancer {
public:
    /**
     * @brief Creates a load balancer with cfg.numServers idle servers.
     * @param name Label used in logs, e.g. "Main", "Streaming".
     * @param cfg Settings (task times, cooldown, blocked ranges, ...).
     * @param log Logger shared by the simulation.
     */
    LoadBalancer(const std::string& name, const Config& cfg, Logger& log);

    /** @brief Deletes every remaining server. */
    ~LoadBalancer();

    LoadBalancer(const LoadBalancer&) = delete;            ///< Not copyable (owns raw pointers).
    LoadBalancer& operator=(const LoadBalancer&) = delete; ///< Not copyable (owns raw pointers).

    /**
     * @brief Fills the queue with random requests (normally servers x 100).
     * @param n Number of requests to generate.
     */
    void fillQueue(int n);

    /**
     * @brief Passes a request through the firewall and queues it if allowed.
     * @param r Incoming request.
     * @return true if queued, false if blocked.
     */
    bool receive(const Request& r);

    /**
     * @brief Runs one clock cycle: dispatch, process, scaling check, clock++.
     */
    void tick();

    /**
     * @brief Writes the summary (queue sizes, task range, counters, server status).
     * @param out Stream to write to.
     */
    void printSummary(std::ostream& out) const;

    /** @return Requests waiting in the queue. */
    int queueSize() const;
    /** @return Current number of servers. */
    int serverCount() const;
    /** @return Servers currently processing a request. */
    int busyServers() const;
    /** @return Current clock cycle. */
    int getClock() const;
    /** @return Counters for this load balancer. */
    const Stats& getStats() const;
    /** @return This load balancer's name. */
    const std::string& getName() const;

private:
    /** @brief Gives the next queued request to every idle server. */
    void dispatch();

    /** @brief Adds or removes one server when the queue leaves the 50x-80x band and the cooldown has passed. */
    void checkScaling();

    /** @brief Allocates one new server. */
    void addServer();

    /**
     * @brief Deletes one idle server, never going below one server.
     * @return false if no server could be removed (all busy or only one left).
     */
    bool removeServer();

    std::string name;                 ///< Label used in logs.
    Config cfg;                       ///< Settings for this balancer.
    Logger& log;                      ///< Shared logger.
    RequestQueue queue;               ///< Requests waiting for a server.
    std::vector<WebServer*> servers;  ///< Dynamically allocated server pool.
    IPBlocker firewall;               ///< Rejects blocked IP ranges.
    int clock = 0;                    ///< Current clock cycle.
    int lastScaleTime = 0;            ///< Clock cycle of the last add/remove.
    int nextServerId = 1;             ///< Id for the next server created.
    Stats stats;                      ///< Counters for the summary.
};

#endif
