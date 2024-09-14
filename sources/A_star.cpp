#include "A_star.h"
#include <math.h>

double A_star::euclidean_distance(const int& a, const int& b){
    if(dp_euclidean_distance[a][b] != 0){
        return dp_euclidean_distance[a][b];
    }else{
        return dp_euclidean_distance[a][b] = sqrt(pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2));
    }
}

void A_star::fill_adj_matrix(const vector<vector<double>>& distance_matrix){
    int n = distance_matrix.size();

    //for each node in the matrix verifies the adjacents vertices
    for(int i = 0; i < n; i++){
        vector<pair<int, double>> aux; //the aux vector to do the push_back in the adjcency matrix

        for(int j = 0; j < n; j++){
            if(distance_matrix[i][j]){ //if the distance of the vertex is higher than zero so there is a connection
                aux.push_back(make_pair(j, distance_matrix[i][j]));
            }
        }

        adj_matrix.push_back(aux);
    }
}

//iterates in the list of penultimates searching from the end until reach the start vertex
vector<int> A_star::find_path(const vector<int>& pen, const int& start, int end){
    vector<int> route; //the route who will be returned
    
    vector<int> aux; //the auxiliar vector to stores the reversed route

    aux.push_back(end);
    while(pen[end] != start){
        aux.push_back(pen[end]);
        end = pen[end];
    }
    aux.push_back(start);

    for(int i = aux.size()-1; i >= 0; i--){
        route.push_back(aux[i]);
    }

    return route;
}

A_star::A_star(){}

A_star::A_star(const vector<vector<double>>& distance_matrix, const vector<double>& x, const vector<double>& y){
    this->x = x;
    this->y = y;

    //resizes the euclidean distance matrix
    dp_euclidean_distance.resize(distance_matrix.size());
    for(int i = 0; i < dp_euclidean_distance.size(); i++){
        dp_euclidean_distance[i].resize(distance_matrix[i].size());
    }

    fill_adj_matrix(distance_matrix);
}

Route A_star::shortest_path(const int& start, const int& end){
    Route route;

    if(start == end){
        cout << "Invalid enters!\n";
        return route;
    }

    int n = adj_matrix.size();

    // vector<bool> visited(n, 0);             //initialize all as false
    // list<int> unvisited;
    for(int i = 0; i < n; i++){
        // unvisited.push_back(i);
    }
    vector<double> distance(n, INFINITY);   //initialize all as infinity
    distance[start] = 0;                    //changes only the starting vertex to 0
    vector<int> penultimates(n, -1);        //vector of the penultimates vertex before reach the vertex


    // a_star_algorithm(start, distance, unvisited, penultimates); //runs the dijkstra algorithm

    route.obj = distance[end]; //the distance to the desired vertex 
    route.path = find_path(penultimates, start, end); //find the path from the start to the end

    return route;
}

