/**
 * @file IPBlocker.h
 * @brief Declares IPBlocker, a firewall that rejects IP address ranges.
 */

#ifndef IPBLOCKER_H
#define IPBLOCKER_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

/**
 * @class IPBlocker
 * @brief Firewall / DOS protection: rejects requests whose source IP falls
 *        inside any configured range.
 *
 * Each address is converted to one 32-bit number, so checking a range is
 * just low <= ip <= high.
 */
class IPBlocker {
public:
    /**
     * @brief Blocks every address from lo to hi, inclusive.
     * @param lo First address of the range, e.g. "10.0.0.0".
     * @param hi Last address of the range, e.g. "10.255.255.255".
     * @return false if either address is not a valid IPv4 address.
     */
    bool addRange(const std::string& lo, const std::string& hi);

    /**
     * @brief Blocks a range written as "lo-hi", as it appears in config.txt.
     * @param range Text such as "10.0.0.0-10.255.255.255".
     * @return false if the text is not a valid range.
     */
    bool addRange(const std::string& range);

    /**
     * @brief Checks an address against every blocked range.
     * @param ip IPv4 address to test.
     * @return true if the address is inside a blocked range.
     */
    bool isBlocked(const std::string& ip) const;

    /** @return Number of blocked ranges. */
    int rangeCount() const;

    /**
     * @brief Converts dotted IPv4 text to a 32-bit number.
     * @param ip Address such as "192.168.1.5".
     * @param out Receives a<<24 | b<<16 | c<<8 | d on success.
     * @return false if ip is not four numbers 0-255 separated by dots.
     */
    static bool toInt(const std::string& ip, uint32_t& out);

private:
    std::vector<std::pair<uint32_t, uint32_t>> ranges; ///< Blocked [low, high] pairs.
};

#endif
