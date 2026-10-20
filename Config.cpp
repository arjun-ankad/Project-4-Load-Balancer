/**
 * @file Config.cpp
 * @brief Implements Config::load.
 */

#include "Config.h"

#include <fstream>

namespace {
/// Removes leading and trailing spaces and tabs.
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = s.find_last_not_of(" \t\r");
    return s.substr(start, end - start + 1);
}
}

bool Config::load(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        size_t eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }
        std::string key = trim(line.substr(0, eq));
        std::string value = trim(line.substr(eq + 1));
        try {
            if (key == "servers") numServers = std::stoi(value);
            else if (key == "run_time") runTime = std::stoi(value);
            else if (key == "scale_cooldown") scaleCooldown = std::stoi(value);
            else if (key == "min_task_time") minTaskTime = std::stoi(value);
            else if (key == "max_task_time") maxTaskTime = std::stoi(value);
            else if (key == "arrival_chance") arrivalChance = std::stoi(value);
            else if (key == "max_arrivals") maxArrivals = std::stoi(value);
            else if (key == "status_interval") statusInterval = std::stoi(value);
            else if (key == "seed") seed = static_cast<unsigned int>(std::stoul(value));
            else if (key == "verbose") verbose = (value == "true" || value == "1");
            else if (key == "log_file") logFile = value;
            else if (key == "blocked_range") blockedRanges.push_back(value);
        } catch (...) {
            // a bad number keeps the default for that key
        }
    }
    return true;
}
