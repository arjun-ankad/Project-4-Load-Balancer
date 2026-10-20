/**
 * @file Request.cpp
 * @brief Implements random request generation.
 */

#include "Request.h"

std::mt19937& rng() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

void seedRng(unsigned int seed) {
    rng().seed(seed);
}

int randomInt(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng());
}

std::string randomIP() {
    return std::to_string(randomInt(0, 255)) + "." +
           std::to_string(randomInt(0, 255)) + "." +
           std::to_string(randomInt(0, 255)) + "." +
           std::to_string(randomInt(0, 255));
}

Request makeRandomRequest(int minTime, int maxTime) {
    static int nextId = 1;
    Request r;
    r.id = nextId++;
    r.ipIn = randomIP();
    r.ipOut = randomIP();
    r.time = randomInt(minTime, maxTime);
    r.jobType = (randomInt(0, 1) == 0) ? 'P' : 'S';
    return r;
}
