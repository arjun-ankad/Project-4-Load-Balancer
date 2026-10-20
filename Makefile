# Makefile for the Ankad Load Balancer
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = loadbalancer
SRCS = main.cpp Request.cpp RequestQueue.cpp WebServer.cpp LoadBalancer.cpp IPBlocker.cpp Config.cpp Logger.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

docs:
	doxygen Doxyfile

clean:
	rm -f $(TARGET) $(OBJS) log.txt
	rm -rf docs

.PHONY: all docs clean
