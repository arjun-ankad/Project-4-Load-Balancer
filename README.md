# Ankad Load Balancer

CSCE 412 Project 4: a C++ simulation of a load balancer distributing web requests across a pool of web servers, with dynamic server scaling, an IP range firewall, a config file, and colored verbose/quiet logging.

## Build and run

```
make            # builds ./loadbalancer
./loadbalancer  # reads config.txt, then asks for servers and run time
make docs       # Doxygen HTML into docs/html (needs doxygen installed)
make clean
```

## Files

| File | Purpose |
|---|---|
| `main.cpp` | Driver: config, user input, main loop, summary |
| `Request.h/.cpp` | Request struct and random request generation |
| `RequestQueue.h/.cpp` | FIFO queue of requests |
| `WebServer.h/.cpp` | Processes one request at a time |
| `LoadBalancer.h/.cpp` | Queue, server pool, dispatch, scaling, stats |
| `IPBlocker.h/.cpp` | IP range firewall |
| `Config.h/.cpp` | Reads `config.txt` |
| `Logger.h/.cpp` | Colored console output and `log.txt` |
| `Stats.h` | Summary counters |

## Configuration

See `config.txt`. `seed=0` gives a different run each time; any other value repeats a run exactly.
