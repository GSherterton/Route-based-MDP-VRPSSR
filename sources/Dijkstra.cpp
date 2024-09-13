#include "Dijkstra.h"

void Dijkstra::fill_adj_matrix(const vector<vector<double>>& distance_matrix){
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
vector<int> Dijkstra::find_path(const vector<int>& pen, const int& start, int end){
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

Dijkstra::Dijkstra(){}

Dijkstra::Dijkstra(const vector<vector<double>>& distance_matrix){
    fill_adj_matrix(distance_matrix);    
}

void Dijkstra::dijkstra_algorithm(const int& start, vector<double>& distance, vector<bool>& visited, vector<int>& penultimates){
    int n = adj_matrix.size(); //gets the quantity of vertices

    //finds the shortest path from the start vertex to all other vertices
    for(int i = 0; i < n; i++){
        int index_aux = -1; //marks the index aux as not changed

        for(int j = 0; j < n; j++){//pode mudar isso para uma lista de visitados para fazer menos iteracoes
            if(!visited[j] && (index_aux == -1 || distance[j] < distance[index_aux])){
                index_aux = j;
            }
        }

        /*//if the unvisited was a list of the vertices not visited
        for(auto it : unvisited){
            if(index_aux == -1 || distance[it] < distance[index_aux]){
                index_aux = it;
            }
        }
        */

        if(distance[index_aux] == INFINITY){ //stops if had an isolated vertex
            break;
        }

        visited[index_aux] = true;

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

Route Dijkstra::shortest_path(const int& start, const int& end){
    Route route;

    if(start == end){
        cout << "Invalid enters!\n";
        return route;
    }

    int n = adj_matrix.size();

    vector<bool> visited(n, 0);             //initialize all as false
    vector<double> distance(n, INFINITY);   //initialize all as infinity
    distance[start] = 0;                    //changes only the starting vertex to 0
    vector<int> penultimates(n, -1);                 //vector of the penultimates vertex before reach the vertex

    dijkstra_algorithm(start, distance, visited, penultimates); //runs the dijkstra algorithm

    route.obj = distance[end]; //the distance to the desired vertex 
    route.path = find_path(penultimates, start, end); //find the path from the start to the end

    return route;
}
