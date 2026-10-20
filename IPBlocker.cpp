/**
 * @file IPBlocker.cpp
 * @brief Implements IPBlocker.
 */

#include "IPBlocker.h"

#include <sstream>

bool IPBlocker::toInt(const std::string& ip, uint32_t& out) {
    std::stringstream ss(ip);
    std::string part;
    uint32_t value = 0;
    int count = 0;
    while (std::getline(ss, part, '.')) {
        if (part.empty() || part.size() > 3 || ++count > 4) {
            return false;
        }
        for (char c : part) {
            if (c < '0' || c > '9') {
                return false;
            }
        }
        int octet = std::stoi(part);
        if (octet > 255) {
            return false;
        }
        value = (value << 8) | static_cast<uint32_t>(octet);
    }
    if (count != 4) {
        return false;
    }
    out = value;
    return true;
}

bool IPBlocker::addRange(const std::string& lo, const std::string& hi) {
    uint32_t low, high;
    if (!toInt(lo, low) || !toInt(hi, high)) {
        return false;
    }
    if (low > high) {
        std::swap(low, high);
    }
    ranges.push_back({low, high});
    return true;
}

bool IPBlocker::addRange(const std::string& range) {
    size_t dash = range.find('-');
    if (dash == std::string::npos) {
        return false;
    }
    return addRange(range.substr(0, dash), range.substr(dash + 1));
}

bool IPBlocker::isBlocked(const std::string& ip) const {
    uint32_t value;
    if (!toInt(ip, value)) {
        return true; // malformed addresses are rejected
    }
    for (const auto& r : ranges) {
        if (r.first <= value && value <= r.second) {
            return true;
        }
    }
    return false;
}

int IPBlocker::rangeCount() const {
    return static_cast<int>(ranges.size());
}
