/**
 * @file Logger.h
 * @brief Declares Logger, which writes colored console output and a plain log file.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

/**
 * @namespace Color
 * @brief ANSI escape codes used to color console events.
 */
namespace Color {
const std::string RESET  = "\033[0m";  ///< Back to the default color.
const std::string GREEN  = "\033[32m"; ///< Server added.
const std::string YELLOW = "\033[33m"; ///< Server removed.
const std::string RED    = "\033[31m"; ///< Request blocked.
const std::string BLUE   = "\033[34m"; ///< Start and end summaries.
const std::string GRAY   = "\033[90m"; ///< Status snapshots.
}

/**
 * @class Logger
 * @brief Sends simulation events to the console (in color) and to a log
 *        file (plain text).
 *
 * In verbose mode events are written as they happen. In quiet mode only
 * summaries are written.
 */
class Logger {
public:
    /**
     * @brief Opens the log file.
     * @param path File to write; it is overwritten.
     * @param verbose true for verbose mode, false for quiet mode.
     */
    Logger(const std::string& path, bool verbose);

    /**
     * @brief Logs one event, only in verbose mode.
     * @param color One of the Color codes, used on the console only.
     * @param msg Event text.
     */
    void event(const std::string& color, const std::string& msg);

    /**
     * @brief Logs summary text in both modes.
     * @param msg Summary text; may contain several lines.
     */
    void summary(const std::string& msg);

    /** @return true if the logger is in verbose mode. */
    bool isVerbose() const;

private:
    std::ofstream file; ///< Plain-text log file.
    bool verbose;       ///< Verbose (true) or quiet (false).
};

#endif
