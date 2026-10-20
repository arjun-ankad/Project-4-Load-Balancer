/**
 * @file Logger.cpp
 * @brief Implements Logger.
 */

#include "Logger.h"

#include <iostream>

Logger::Logger(const std::string& path, bool verbose) : file(path), verbose(verbose) {}

void Logger::event(const std::string& color, const std::string& msg) {
    if (!verbose) {
        return;
    }
    std::cout << color << msg << Color::RESET << '\n';
    if (file) {
        file << msg << '\n';
    }
}

void Logger::summary(const std::string& msg) {
    std::cout << Color::BLUE << msg << Color::RESET << '\n';
    if (file) {
        file << msg << '\n';
    }
}

bool Logger::isVerbose() const {
    return verbose;
}
