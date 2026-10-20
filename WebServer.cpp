/**
 * @file WebServer.cpp
 * @brief Implements WebServer.
 */

#include "WebServer.h"

WebServer::WebServer(int id) : id(id) {}

void WebServer::assign(const Request& r) {
    current = r;
    timeLeft = r.time;
    busy = true;
}

bool WebServer::tick() {
    if (!busy) {
        return false;
    }
    timeLeft--;
    if (timeLeft <= 0) {
        busy = false;
        completed++;
        return true;
    }
    return false;
}

bool WebServer::isIdle() const {
    return !busy;
}

int WebServer::getId() const {
    return id;
}

int WebServer::getCompleted() const {
    return completed;
}

const Request& WebServer::getCurrent() const {
    return current;
}
