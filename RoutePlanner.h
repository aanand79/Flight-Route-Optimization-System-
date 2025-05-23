#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "Graph.h"
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class RoutePlanner {
private:
    Graph& graph;

public:
    RoutePlanner(Graph& g) : graph(g) {}

    void findCheapestRoute(const std::string& start, const std::string& end) {
        findRoute(start, end, true);
    }

    void findFastestRoute(const std::string& start, const std::string& end) {
        findRoute(start, end, false);
    }

    void findRoute(const std::string& start, const std::string& end, bool byCost) {
        std::unordered_map<std::string, double> dist;
        std::unordered_map<std::string, std::string> prev;

        // Use the internal routes map to get city names
        for (const auto& entry : graph.getRoutes()) {
            dist[entry.first] = std::numeric_limits<double>::infinity();
        }

        dist[start] = 0.0;

        auto cmp = [&](const std::string& a, const std::string& b) {
            return dist[a] > dist[b];
        };

        std::priority_queue<std::string, std::vector<std::string>, decltype(cmp)> pq(cmp);
        pq.push(start);

        while (!pq.empty()) {
            std::string current = pq.top();
            pq.pop();

            for (const auto& flight : graph.getFlights(current)) {
                double weight = byCost ? flight.cost : flight.time;
                if (dist[current] + weight < dist[flight.destination]) {
                    dist[flight.destination] = dist[current] + weight;
                    prev[flight.destination] = current;
                    pq.push(flight.destination);
                }
            }
        }

        if (dist[end] == std::numeric_limits<double>::infinity()) {
            std::cout << "No route found." << std::endl;
            return;
        }

        std::vector<std::string> path;
        for (std::string at = end; at != ""; at = prev.count(at) ? prev[at] : "") {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        std::cout << (byCost ? "Cheapest" : "Fastest") << " route: ";
        for (const auto& city : path) {
            std::cout << city << (city != end ? " -> " : "");
        }
        std::cout << std::endl;

std::cout << "Total " << (byCost ? "cost: Rs. " + std::to_string(static_cast<int>(dist[end])) 
                                 : "time: " + std::to_string(dist[end]) + " hrs") << std::endl;
    }
};

#endif // ROUTE_PLANNER_H
