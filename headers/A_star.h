#pragma once
#include <vector>
#include "Route.h"

using namespace std;

class A_star{
    private:
        vector<vector<pair<int, double>>> adj_matrix;

        void fill_adj_matrix(const vector<vector<double>>& distance_matrix);
        vector<int> find_path(const vector<int>& pen, const int& start, int end);
    public:
        A_star();
        A_star(const vector<vector<double>>& distance_matrix);

        void a_star_algorithm(const int& start, vector<double>& distance, vector<bool>& visited, vector<int>& penultimates);
        Route shortest_path(const int& start, const int& end);
};