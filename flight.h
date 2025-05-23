#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>

struct Flight {
    std::string destination;
    int cost;
    double time;

    Flight(const std::string& dest, int c, double t)
        : destination(dest), cost(c), time(t) {}
};

#endif
