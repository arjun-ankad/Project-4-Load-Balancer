/**
 * @file main.cpp
 * @brief Driver for the Ankad Load Balancer simulation.
 *
 * TODO (Arjun): the course requires you to write the driver yourself.
 * Follow Figure 2 (workflow diagram) in the design document:
 *
 *  1. Load Config from "config.txt" (cfg.load). Print a warning if missing.
 *  2. Ask the user for the number of servers and the run time; let the
 *     typed values override cfg.numServers and cfg.runTime.
 *     Optionally ask verbose or quiet.
 *  3. If cfg.seed != 0, call seedRng(cfg.seed).
 *  4. Create a Logger(cfg.logFile, cfg.verbose) and a LoadBalancer.
 *  5. fillQueue(servers * 100) and log the starting summary.
 *  6. Loop while the clock is below the run time:
 *       - with arrivalChance % chance, make up to maxArrivals new requests
 *         (makeRandomRequest) and pass each to receive();
 *       - call tick() on the load balancer;
 *       - in verbose mode, every statusInterval cycles log a status line.
 *  7. Log the ending summary (printSummary).
 */

#include <iostream>

#include "Config.h"
#include "LoadBalancer.h"
#include "Logger.h"

int main() {
    std::cout << "Ankad Load Balancer: main() not written yet\n";
    return 0;
}
