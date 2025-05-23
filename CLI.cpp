#include "Graph.h"
#include "RoutePlanner.h"
#include <iostream>
#include <sstream>

void runCLI() {
    Graph graph;
    RoutePlanner planner(graph);

    std::cout << "Flight Route Optimization System\n";
    std::cout << "Type 'help' to see available commands. Type 'exit' to quit.\n";

    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "exit") break;

        else if (cmd == "help") {
            std::cout << "Available commands:\n";
            std::cout << "  add_city [name]                  - Add a city\n";
            std::cout << "  add_flight [from] [to] [cost] [time] - Add a flight\n";
            std::cout << "  show_routes                      - Show all routes\n";
            std::cout << "  cheapest_route [from] [to]      - Find cheapest route\n";
            std::cout << "  fastest_route [from] [to]       - Find fastest route\n";
            std::cout << "  exit                            - Exit the program\n";
        }

        else if (cmd == "add_city") {
            std::string city;
            ss >> city;
            if (!city.empty()) {
                graph.addCity(city);
                std::cout << "City added: " << city << "\n";
            } else {
                std::cout << "Usage: add_city [name]\n";
            }
        }

        else if (cmd == "add_flight") {
            std::string from, to;
            int cost;
            double time;
            ss >> from >> to >> cost >> time;
            if (!from.empty() && !to.empty()) {
                graph.addFlight(from, to, cost, time);
                std::cout << "Flight added: " << from << " -> " << to << "\n";
            } else {
                std::cout << "Usage: add_flight [from] [to] [cost] [time]\n";
            }
        }

        else if (cmd == "show_routes") {
            graph.showRoutes();
        }

        else if (cmd == "cheapest_route") {
            std::string from, to;
            ss >> from >> to;
            if (!from.empty() && !to.empty()) {
                planner.findCheapestRoute(from, to);
            } else {
                std::cout << "Usage: cheapest_route [from] [to]\n";
            }
        }

        else if (cmd == "fastest_route") {
            std::string from, to;
            ss >> from >> to;
            if (!from.empty() && !to.empty()) {
                planner.findFastestRoute(from, to);
            } else {
                std::cout << "Usage: fastest_route [from] [to]\n";
            }
        }

        else {
            std::cout << "Unknown command. Type 'help' to see available commands.\n";
        }
    }
}
