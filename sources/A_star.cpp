#include "A_star.h"
#include <math.h>

//it will be the h
double A_star::euclidean_distance(const int& a, const int& b){
    if(dp_euclidean_distance[a][b] != 0){
        return dp_euclidean_distance[a][b];
    }else{//maybe we could not use the square root because we dont really use this value just to compare, and the [sqrt(a) < sqrt(b) ==> a < b]
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

//the cell_details is like the distance vector, penultimates vector but with the f and h too
void A_star::a_star_algorithm(const int& start, const int& end, vector<double>& objective_distance, vector<double>& distance, vector<double>& euclidean, vector<bool>& closed_list, vector<int>& penultimates){
    int n = adj_matrix.size(); //gets the quantity of vertices

    set<pair<double, int>> open_list; //double is the f and the int is the index of the vertex

    open_list.insert(make_pair(euclidean_distance(start, end), start)); //insert the start vertex in the open list, the objective
                                                                        //distance of it is just the euclidean distance, because
                                                                        //the distance of its path is 0    

    int index_aux;

    while(!open_list.empty()){
        pair<double, int> p = *open_list.begin();
        open_list.erase(open_list.begin());

        index_aux = p.second;
        
        closed_list[index_aux] = 1;

        double gNew, hNew, fNew;

        for(auto edge : adj_matrix[index_aux]){
            if(edge.first == end){ //found the end
                penultimates[edge.first] = index_aux;
                distance[edge.first] = distance[index_aux] + edge.second;
                return;
            }else if(closed_list[edge.first] == false){
                gNew = distance[index_aux] + edge.second;
                hNew = euclidean_distance(edge.first, end);
                fNew = gNew + hNew;

                if (objective_distance[edge.first] == INFINITY || objective_distance[edge.first] > fNew) {
                    open_list.insert(make_pair(fNew, edge.first));

                    for(auto it : open_list){
                        cout << it.second << ", ";
                    }cout << endl;

                    cout << "Mudando o vertice " << edge.first << endl;

                    objective_distance[edge.first] = fNew;
                    distance[edge.first] = gNew;
                    euclidean[edge.first] = hNew;
                    penultimates[edge.first] = index_aux;
                }
            }
        }
    }
}

Route A_star::shortest_path(const int& start, const int& end){
    Route route;

    if(start == end){
        cout << "Invalid enters!\n";
        return route;
    }

    int n = adj_matrix.size();

    vector<bool> closed_list(n, 0);
    /*
    list<int> unvisited;
    for(int i = 0; i < n; i++){
        unvisited.push_back(i);
    }
    */

    vector<double> objective_distance(n, INFINITY);     //initialize all as infinity
    vector<double> distance(n, INFINITY);               //initialize all as infinity
    vector<double> euclidean(n, INFINITY);              //initialize all as infinity
    objective_distance[start] = 0;                    //changes only the starting vertex to 0
    distance[start] = 0;                    //changes only the starting vertex to 0
    euclidean[start] = 0;                    //changes only the starting vertex to 0
    vector<int> penultimates(n, -1);        //vector of the penultimates vertex before reach the vertex


    a_star_algorithm(start, end, objective_distance, distance, euclidean, closed_list, penultimates); //runs the A* algorithm

    route.obj = distance[end]; //the distance to the desired vertex 
    route.path = find_path(penultimates, start, end); //find the path from the start to the end

    return route;
}

