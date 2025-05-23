#ifndef GRAPH_H
#define GRAPH_H

#include "Flight.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class Graph {
private:
    std::unordered_map<std::string, std::vector<Flight>> routes;

public:
    void addCity(const std::string& name) {
        routes[name]; // creates entry if not present
    }

    void addFlight(const std::string& from, const std::string& to, int cost, double time) {
        routes[from].emplace_back(to, cost, time);
    }

    std::vector<Flight> getFlights(const std::string& city) const {
        auto it = routes.find(city);
        if (it != routes.end())
            return it->second;
        else
            return {};
    }

    const std::unordered_map<std::string, std::vector<Flight>>& getRoutes() const {
        return routes;
    }

    void showRoutes() const {
        for (const auto& pair : routes) {
            for (const Flight& flight : pair.second) {
                std::cout << pair.first << " -> " << flight.destination
                          << " | ₹" << flight.cost
                          << " | " << flight.time << " hrs" << std::endl;
            }
        }
    }

    // Optional helper method if needed elsewhere
    const std::unordered_map<std::string, std::vector<Flight>>& getAllCities() const {
        return routes;
    }
};

#endif // GRAPH_H
