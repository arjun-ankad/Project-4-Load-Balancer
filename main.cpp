/**
 * @file main.cpp
 * @brief Driver for the Ankad Load Balancer simulation.
 *
 * Follows Figure 2 (workflow diagram) in the design document:
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
#include <sstream>

#include "Config.h"
#include "LoadBalancer.h"
#include "Logger.h"
#include "Request.h"

int main() {
    Config cfg;
    if (!cfg.load("config.txt")) {
        std::cout << "Warning: could not open config.txt, using default settings.\n";
    }

    int n;
    std::cout << "Number of servers (default " << cfg.numServers << "): ";
    if (std::cin >> n && n > 0) cfg.numServers = n;
    std::cout << "Run time in clock cycles (default " << cfg.runTime << "): ";
    if (std::cin >> n && n > 0) cfg.runTime = n;

    char mode;
    std::cout << "Verbose (v) or quiet (q)? ";
    if (std::cin >> mode) {
        if (mode == 'v' || mode == 'V') cfg.verbose = true;
        if (mode == 'q' || mode == 'Q') cfg.verbose = false;
    }

    if (cfg.seed != 0) seedRng(cfg.seed);

    Logger log(cfg.logFile, cfg.verbose);
    LoadBalancer lb("Main", cfg, log);

    lb.fillQueue(cfg.numServers * 100);
    std::ostringstream start;
    start << "===== [Main] Start =====\n"
          << "Servers:         " << lb.serverCount() << "\n"
          << "Queue size:      " << lb.queueSize() << "\n"
          << "Task time range: " << cfg.minTaskTime << " - " << cfg.maxTaskTime << " cycles\n";
    log.summary(start.str());

    while (lb.getClock() < cfg.runTime) {
        if (randomInt(1, 100) <= cfg.arrivalChance) {
            int count = randomInt(1, cfg.maxArrivals);
            for (int i = 0; i < count; i++) {
                lb.receive(makeRandomRequest(cfg.minTaskTime, cfg.maxTaskTime));
            }
        }
        lb.tick();

        if (cfg.statusInterval > 0 && lb.getClock() % cfg.statusInterval == 0) {
            log.event(Color::GRAY, "[Main] cycle " + std::to_string(lb.getClock()) +
                      ": STATUS (servers=" + std::to_string(lb.serverCount()) +
                      ", queue=" + std::to_string(lb.queueSize()) + ")");
        }
    }

    std::ostringstream ss;
    lb.printSummary(ss);
    log.summary(ss.str());
    return 0;
}
