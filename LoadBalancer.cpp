/**
 * @file LoadBalancer.cpp
 * @brief Implements LoadBalancer.
 */

#include "LoadBalancer.h"

#include <algorithm>

LoadBalancer::LoadBalancer(const std::string& name, const Config& cfg, Logger& log)
    : name(name), cfg(cfg), log(log) {
    for (const std::string& range : cfg.blockedRanges) {
        firewall.addRange(range);
    }
    for (int i = 0; i < std::max(1, cfg.numServers); i++) {
        servers.push_back(new WebServer(nextServerId++));
    }
    stats.peakServers = serverCount();
    stats.minServers = serverCount();
}

LoadBalancer::~LoadBalancer() {
    for (WebServer* s : servers) {
        delete s;
    }
}

void LoadBalancer::fillQueue(int n) {
    for (int i = 0; i < n; i++) {
        stats.generated++;
        receive(makeRandomRequest(cfg.minTaskTime, cfg.maxTaskTime));
    }
    stats.startQueueSize = queueSize();
    stats.peakQueue = queueSize();
}

bool LoadBalancer::receive(const Request& r) {
    if (firewall.isBlocked(r.ipIn)) {
        stats.blocked++;
        log.event(Color::RED, "[" + name + "] cycle " + std::to_string(clock) +
                  ": BLOCKED request " + std::to_string(r.id) + " from " + r.ipIn);
        return false;
    }
    queue.push(r);
    stats.peakQueue = std::max(stats.peakQueue, queueSize());
    return true;
}

void LoadBalancer::tick() {
    // TODO (Arjun): one clock cycle, following Figure 2 of the design doc.
    //  1. dispatch() so every idle server gets the next request.
    //  2. tick() every server; when it returns true, count stats.processed.
    //  3. checkScaling().
    //  4. clock++.
    clock++;
}

void LoadBalancer::dispatch() {
    // TODO (Arjun): for each server, if it is idle and the queue is not
    // empty, pop the front request and assign() it to that server.
}

void LoadBalancer::checkScaling() {
    // TODO (Arjun): the dynamic scaling rule from section 5 of the design doc.
    //  - Do nothing until cfg.scaleCooldown cycles have passed since lastScaleTime.
    //  - queueSize() > 80 * serverCount()  -> addServer()
    //  - queueSize() < 50 * serverCount()  -> removeServer()
    //  - After a change, set lastScaleTime = clock.
}

void LoadBalancer::addServer() {
    servers.push_back(new WebServer(nextServerId++));
    stats.serversAdded++;
    stats.peakServers = std::max(stats.peakServers, serverCount());
    log.event(Color::GREEN, "[" + name + "] cycle " + std::to_string(clock) +
              ": ADDED server " + std::to_string(nextServerId - 1) +
              " (servers=" + std::to_string(serverCount()) +
              ", queue=" + std::to_string(queueSize()) + ")");
}

bool LoadBalancer::removeServer() {
    if (serverCount() <= 1) {
        return false;
    }
    for (size_t i = 0; i < servers.size(); i++) {
        if (servers[i]->isIdle()) {
            int id = servers[i]->getId();
            delete servers[i];
            servers.erase(servers.begin() + i);
            stats.serversRemoved++;
            stats.minServers = std::min(stats.minServers, serverCount());
            log.event(Color::YELLOW, "[" + name + "] cycle " + std::to_string(clock) +
                      ": REMOVED server " + std::to_string(id) +
                      " (servers=" + std::to_string(serverCount()) +
                      ", queue=" + std::to_string(queueSize()) + ")");
            return true;
        }
    }
    return false;
}

void LoadBalancer::printSummary(std::ostream& out) const {
    // TODO (Arjun): decide what the summary shows. The log rubric needs at least:
    //  starting queue size, ending queue size, task time range,
    //  servers added/removed, active vs inactive servers, blocked requests,
    //  plus 3 more useful facts (see DEVLOG.md for ideas).
    out << "[" << name << "] summary not written yet\n";
}

int LoadBalancer::queueSize() const {
    return queue.size();
}

int LoadBalancer::serverCount() const {
    return static_cast<int>(servers.size());
}

int LoadBalancer::busyServers() const {
    int busy = 0;
    for (const WebServer* s : servers) {
        if (!s->isIdle()) {
            busy++;
        }
    }
    return busy;
}

int LoadBalancer::getClock() const {
    return clock;
}

const Stats& LoadBalancer::getStats() const {
    return stats;
}

const std::string& LoadBalancer::getName() const {
    return name;
}
