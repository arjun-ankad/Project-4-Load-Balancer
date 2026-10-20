/**
 * @file Request.h
 * @brief Declares the Request struct and helpers that generate random requests.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <random>
#include <string>

/**
 * @struct Request
 * @brief One simulated web request waiting to be processed by a WebServer.
 *
 * A Request is plain data: who sent it, where the result goes, how many
 * clock cycles it needs, and what kind of job it is.
 */
struct Request {
    int id = 0;            ///< Sequential id, used in logs.
    std::string ipIn;      ///< IPv4 address of the requester, e.g. "192.168.4.17".
    std::string ipOut;     ///< IPv4 address the result is sent to.
    int time = 0;          ///< Processing time in clock cycles (always >= 1).
    char jobType = 'P';    ///< 'P' for processing or 'S' for streaming.
};

/**
 * @brief Shared random number generator used by the whole simulation.
 * @return Reference to a single std::mt19937 engine.
 */
std::mt19937& rng();

/**
 * @brief Seeds the shared random number generator.
 * @param seed Seed value; the same seed reproduces the same run.
 */
void seedRng(unsigned int seed);

/**
 * @brief Returns a uniformly random integer in [low, high].
 * @param low Smallest value that can be returned.
 * @param high Largest value that can be returned.
 * @return Random integer between low and high, inclusive.
 */
int randomInt(int low, int high);

/**
 * @brief Generates a random IPv4 address string.
 * @return Address of four random octets 0-255 joined by dots.
 */
std::string randomIP();

/**
 * @brief Builds a request with random IPs, time and job type.
 * @param minTime Shortest processing time in clock cycles.
 * @param maxTime Longest processing time in clock cycles.
 * @return A new Request with the next sequential id.
 */
Request makeRandomRequest(int minTime, int maxTime);

#endif
