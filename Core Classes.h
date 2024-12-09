#ifndef CORE_CLASSES_H
#define CORE_CLASSES_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
//#include "DijkstraAlgorithm.h"

#endif

class _Intersection {
public:
    int id;
    std::string name;

    // Parameterized constructor
    _Intersection(int id, const std::string& name) : id(id), name(name) {}

    // Default constructor
    _Intersection() : id(0), name("") {}

    // Getter for id
    int getId() const {
        return id;
    }

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Other methods if any...
};


class Road {
public:
    int start;
    int end;
    double distance;
    double traffic;

    // Constructor
    Road(int start, int end, double distance, double traffic = 0.0)
        : start(start), end(end), distance(distance), traffic(traffic) {}

    // Getter for start
    int getStart() const {
        return start;
    }

    // Getter for end
    int getEnd() const {
        return end;
    }

    // Getter for distance
    double getDistance() const {
        return distance;
    }

    // Getter for traffic
    double getTraffic() const {
        return traffic;
    }
};


class Graph {
public:
    std::unordered_map<int, _Intersection> _Intersections;
    std::unordered_map<int, std::vector<Road>> adjacencyList;

    // Add an _Intersection to the graph
    void add_Intersection(int id, const std::string& name) {
        _Intersections[id] = _Intersection(id, name);
    }

    // Add a road to the graph
    void addRoads(int start, int end, double distance, double traffic = 0.0) {
        adjacencyList[start].push_back(Road(start, end, distance, traffic));
    }

    // Load graph data from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string line;
        bool isReading_Intersections = false;
        bool isReadingRoads = false;

        while (std::getline(infile, line)) {
            // Skip comments or empty lines
            if (line.empty() || line[0] == '#') {
                if (line == "# _Intersections (ID, Name)") isReading_Intersections = true, isReadingRoads = false;
                if (line == "# Roads (StartID, EndID, Distance, Traffic)") isReadingRoads = true, isReading_Intersections = false;
                continue;
            }

            std::istringstream ss(line);
            if (isReading_Intersections) {
                int id;
                std::string name;
                char delim;

                ss >> id >> delim >> name;
                if (delim == ',') {
                    add_Intersection(id, name);
                }
            } else if (isReadingRoads) {
                int start, end;
                double distance, traffic;
                char delim;

                ss >> start >> delim >> end >> delim >> distance >> delim >> traffic;
                if (delim == ',') {
                    addRoads(start, end, distance, traffic);
                }
            }
        }

        infile.close();
        std::cout << "Graph data loaded successfully from " << filename << std::endl;
    }

    // Save graph data to a file
    void saveToFile(const std::string& filename) const {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        // Save _Intersections
        outfile << "# _Intersections (ID, Name)" << std::endl;
        for (const auto& [id, _Intersection] : _Intersections) {
            outfile << id << "," << _Intersection.name << std::endl;
        }

        // Save roads
        outfile << "# Roads (StartID, EndID, Distance, Traffic)" << std::endl;
        for (const auto& [start, roads] : adjacencyList) {
            for (const auto& road : roads) {
                outfile << road.start << "," << road.end << "," << road.distance << "," << road.traffic << std::endl;
            }
        }

        outfile.close();
        std::cout << "Graph data saved successfully to " << filename << std::endl;
    }
   
    void displayMap() {
    // Display _Intersections
    for (const auto& _Intersection : _Intersections) {
        std::cout << "_Intersection ID: " << _Intersection.second.getId()
                  << ", Name: " << _Intersection.second.getName() << std::endl;
    }

    // Display roads between _Intersections
    std::cout << "\nRoads between _Intersections:\n";
    for (const auto& [start, roads] : adjacencyList) {
        for (const auto& road : roads) {
            std::cout << "Road from _Intersection " << road.getStart() << " to " << road.getEnd()
                      << " with distance: " << road.getDistance() << " km and traffic: " << road.getTraffic() << std::endl;
        }
    }
   }

  void findShortestPath(int startId, int endId);
};

// DjikstrasAlgorithm
void Graph::findShortestPath(int startId, int endId) {
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;
    std::unordered_map<int, bool> visited; // Added to track visited nodes

    auto compare = [&distances](int a, int b) {
        return distances[a] > distances[b];
    };
    std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);

    // Initialize distances and previous nodes
    for (const auto& _Intersection : _Intersections) {
        distances[_Intersection.first] = std::numeric_limits<double>::infinity();
        previous[_Intersection.first] = -1;
        visited[_Intersection.first] = false; // Initialize visited map
    }

    distances[startId] = 0;
    pq.push(startId);

    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();

        // Skip already visited nodes
        if (visited[current]) {
            continue;
        }
        visited[current] = true; // Mark the current node as visited

        if (current == endId) {
            break; // Stop early if we reach the destination
        }

        // Update distances to neighbors
        for (const Road& road : adjacencyList[current]) {
            int neighbor = road.getEnd();
            double newDistance = distances[current] + road.getDistance();

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
                pq.push(neighbor);
            }
        }
    }

    // Print the shortest path
    if (distances[endId] == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from _Intersection " << startId << " to " << endId << std::endl;
    } else {
        std::cout << "Shortest path from _Intersection " << startId << " to _Intersection " << endId << ":\n";
        std::vector<int> path;
        double totalWeight = distances[endId];
        
        for (int at = endId; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        // Display the path
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << "\nTotal weight: " << totalWeight << std::endl;
    }
}


