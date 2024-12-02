#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>
#include <iostream>
#include <algorithm>

#include "Core Classes.h"

void Graph::findShortestPath(int startId, int endId) {
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;
    auto compare = [&distances](int a, int b) {
        return distances[a] > distances[b];
    };
    std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);

    for (const auto& intersection : intersections) {
        distances[intersection.first] = std::numeric_limits<double>::infinity();
        previous[intersection.first] = -1;
    }

    distances[startId] = 0;
    pq.push(startId);

    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();

        if (adjacencyList.find(current) != adjacencyList.end()) {
            for (const auto& road : adjacencyList[current]) {
                int neighbor = (road.start == current) ? road.end : road.start;
                double newDist = distances[current] + road.distance;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    previous[neighbor] = current;
                    pq.push(neighbor);
                }
            }
        }
    }

    // Print the shortest path
    if (distances[endId] == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from Intersection " << startId << " to " << endId << std::endl;
    } else {
        std::cout << "Shortest path distance: " << distances[endId] << std::endl;
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
}

