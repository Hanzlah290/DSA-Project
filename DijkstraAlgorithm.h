#ifndef DJIKSTRAS_ALGORITHM_H
#define DJIKSTRAS_ALGORITHM_H


#include "Core Classes.h"
#endif // DJIKSTRAS_ALGORITHM_H

class Graph {
public:
    void findShortestPath(int startId, int endId);
};



/*void Graph::findShortestPath(int startId, int endId) {
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
        for (const Road& Roads : adjacencyList[current]) {
            int neighbor = Roads.getEnd();
            double newDistance = distances[current] + Roads.getDistance();

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
        std::cout << "Shortest path distance: " << distances[endId] << " km\n";
        std::vector<int> path;
        for (int at = endId; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        std::cout << "Path: ";
        for (int id : path) {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }
}*/



