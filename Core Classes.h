#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

class Intersection {
public:
    int id;
    std::string name;

    Intersection(int id, const std::string& name) : id(id), name(name) {}
};

class Road {
public:
    int start;
    int end;
    double distance;
    double traffic;

    Road(int start, int end, double distance, double traffic = 0.0)
        : start(start), end(end), distance(distance), traffic(traffic) {}
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
};
