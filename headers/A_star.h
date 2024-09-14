#pragma once
#include <vector>
#include "Route.h"

#define INFINITY 1000000000

using namespace std;

class A_star{
    private:
        vector<vector<pair<int, double>>> adj_matrix;
        vector<double> x;
        vector<double> y;

        vector<vector<double>> dp_euclidean_distance; //stores the values that already has been calculated

        double euclidean_distance(const int& a, const int& b); //calculate the euclidean distance of the vertex a to vertex b
        void fill_adj_matrix(const vector<vector<double>>& distance_matrix);
        vector<int> find_path(const vector<int>& pen, const int& start, int end);
    public:
        A_star();
        A_star(const vector<vector<double>>& distance_matrix, const vector<double>& x, const vector<double>& y);

        void a_star_algorithm(const int& start, vector<double>& distance, vector<bool>& visited, vector<int>& penultimates);
        Route shortest_path(const int& start, const int& end);
};