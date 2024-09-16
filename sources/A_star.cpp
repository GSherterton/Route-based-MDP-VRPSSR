#include "A_star.h"
#include <math.h>

//it will be the h
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

//the cell_details is like the distance vector, penultimates vector but with the f and h too
void A_star::a_star_algorithm(const int& start, const int& end, vector<double>& objective_distance, vector<double>& distance, vector<double>& euclidean, vector<bool>& closed_list, vector<int>& penultimates){
    int n = adj_matrix.size(); //gets the quantity of vertices

    set<pair<double, int>> open_list; //double is the f and the int is the index of the vertex

    open_list.insert(make_pair(0, start)); //insert the start vertex in the open list

    int vertex_index;

    while(!open_list.empty()){
        pair<double, int> p = *open_list.begin();
        open_list.erase(open_list.begin());

        vertex_index = p.second;
        
        closed_list[vertex_index] = 1;

        double gNew, hNew, fNew;

        pair<int, double> iterated_adj;

        //substituir por um for each
        for(int i = 0; i < adj_matrix[vertex_index].size(); i++){
            iterated_adj = adj_matrix[vertex_index][i];
            if(iterated_adj.first == end){
                //found the end vertex
                penultimates[iterated_adj.first] = vertex_index;
                return;
            }else if(closed_list[iterated_adj.first] == false){
                gNew = objective_distance[iterated_adj.first] + iterated_adj.second;
                hNew = euclidean_distance(iterated_adj.first, end);
                fNew = gNew + hNew;
            }
        }






        int index_aux = -1; //marks the index aux as not changed

        return;
    //-------------------------------------------------------------------------------------------------
        

        if(distance[index_aux] == INFINITY){ //stops if had an isolated vertex
            break;
        }

        //visited[index_aux] = true;

        for(auto edge : adj_matrix[index_aux]){ //iterates in the adjacent vertices of the actual vertex (index aux)
            double soma = distance[index_aux] + edge.second; //makes the sum of, the actual lower distance from the start
                                                             //to the index aux, with the distance of theindex aux to the
                                                             //iterated vertex

            if(distance[edge.first] > soma){ //verifies if this sum if lower than the actual lowest distance from this vertex to the iterated
                distance[edge.first] = soma; //if true updates this lowest distance
                penultimates[edge.first] = index_aux; //saves the new penultimate vertex
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

