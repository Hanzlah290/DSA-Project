#ifndef CORE_CLASSES_H
#define CORE_CLASSES_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

#endif

class Intersection {
public:
    int id;
    std::string name;

    // Parameterized constructor
    Intersection(int id, const std::string& name) : id(id), name(name) {}

    // Default constructor
    Intersection() : id(0), name("") {}

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
    std::unordered_map<int, Intersection> intersections;
    std::unordered_map<int, std::vector<Road>> adjacencyList;

    // Add an intersection to the graph
    void addIntersection(int id, const std::string& name) {
        intersections[id] = Intersection(id, name);
    }

    // Add a road to the graph
    void addRoad(int start, int end, double distance, double traffic = 0.0) {
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
        bool isReadingIntersections = false;
        bool isReadingRoads = false;

        while (std::getline(infile, line)) {
            // Skip comments or empty lines
            if (line.empty() || line[0] == '#') {
                if (line == "# Intersections (ID, Name)") isReadingIntersections = true, isReadingRoads = false;
                if (line == "# Roads (StartID, EndID, Distance, Traffic)") isReadingRoads = true, isReadingIntersections = false;
                continue;
            }

            std::istringstream ss(line);
            if (isReadingIntersections) {
                int id;
                std::string name;
                char delim;

                ss >> id >> delim >> name;
                if (delim == ',') {
                    addIntersection(id, name);
                }
            } else if (isReadingRoads) {
                int start, end;
                double distance, traffic;
                char delim;

                ss >> start >> delim >> end >> delim >> distance >> delim >> traffic;
                if (delim == ',') {
                    addRoad(start, end, distance, traffic);
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

        // Save intersections
        outfile << "# Intersections (ID, Name)" << std::endl;
        for (const auto& [id, intersection] : intersections) {
            outfile << id << "," << intersection.name << std::endl;
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
    // Display intersections
    for (const auto& intersection : intersections) {
        std::cout << "Intersection ID: " << intersection.second.getId()
                  << ", Name: " << intersection.second.getName() << std::endl;
    }

    // Display roads between intersections
    std::cout << "\nRoads between intersections:\n";
    for (const auto& [start, roads] : adjacencyList) {
        for (const auto& road : roads) {
            std::cout << "Road from Intersection " << road.getStart() << " to " << road.getEnd()
                      << " with distance: " << road.getDistance() << " km and traffic: " << road.getTraffic() << std::endl;
        }
    }
   }

  void findShortestPath(int startId, int endId);
};

