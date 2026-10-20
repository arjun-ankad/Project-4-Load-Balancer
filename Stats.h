/**
 * @file Stats.h
 * @brief Declares Stats, the counters reported in the log summary.
 */

#ifndef STATS_H
#define STATS_H

/**
 * @struct Stats
 * @brief Running totals for one LoadBalancer, printed in the start and end summaries.
 */
struct Stats {
    int startQueueSize = 0;   ///< Queue size after the initial fill.
    int generated = 0;        ///< Requests created (initial fill + new arrivals).
    int processed = 0;        ///< Requests finished by a server.
    int blocked = 0;          ///< Requests rejected by the IPBlocker.
    int serversAdded = 0;     ///< Servers added by scaling.
    int serversRemoved = 0;   ///< Servers removed by scaling.
    int peakServers = 0;      ///< Most servers at any time.
    int minServers = 0;       ///< Fewest servers at any time.
    int peakQueue = 0;        ///< Largest queue size seen.
};

#endif
