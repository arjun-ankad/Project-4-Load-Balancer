/**
 * @file Config.h
 * @brief Declares Config, the settings read from config.txt.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

/**
 * @class Config
 * @brief Simulation settings loaded from a key=value file, so the load
 *        balancer can be tuned without recompiling.
 *
 * Every field has a default, so a missing file or key still produces a
 * working run.
 */
class Config {
public:
    int numServers = 10;          ///< Starting number of web servers.
    int runTime = 10000;          ///< Clock cycles to simulate.
    int scaleCooldown = 50;       ///< Cycles to wait after adding/removing a server (n).
    int minTaskTime = 3;          ///< Shortest request processing time.
    int maxTaskTime = 500;        ///< Longest request processing time.
    int arrivalChance = 30;       ///< Percent chance a new request arrives each cycle.
    int maxArrivals = 1;          ///< Most new requests that can arrive in one cycle.
    int statusInterval = 1000;    ///< Cycles between status snapshots in verbose mode.
    unsigned int seed = 0;        ///< Random seed; 0 means a different run each time.
    bool verbose = true;          ///< Verbose (events) or quiet (summaries only).
    std::string logFile = "log.txt";        ///< Where the log is written.
    std::vector<std::string> blockedRanges; ///< Ranges such as "10.0.0.0-10.255.255.255".

    /**
     * @brief Reads settings from a file of key=value lines.
     *
     * Blank lines and lines starting with # are ignored. blocked_range may
     * appear more than once. Unknown keys are ignored.
     *
     * @param path Path to the configuration file.
     * @return false if the file could not be opened (defaults are kept).
     */
    bool load(const std::string& path);
};

#endif
