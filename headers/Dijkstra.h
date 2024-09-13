#pragma once
#include <vector>
#include <list>
#include "Route.h"

#define INFINITY 1000000000

using namespace std;

class Dijkstra{
    private:
        vector<vector<pair<int, double>>> adj_matrix;

        void fill_adj_matrix(const vector<vector<double>>& distance_matrix);
        vector<int> find_path(const vector<int>& pen, const int& start, int end);
    public:
        Dijkstra();
        Dijkstra(const vector<vector<double>>& distance_matrix);

        void dijkstra_algorithm(const int& start, vector<double>& distance, list<int>& unvisited, vector<int>& penultimates);
        Route shortest_path(const int& start, const int& end);
};