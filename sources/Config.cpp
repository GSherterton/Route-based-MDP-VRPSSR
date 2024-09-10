#include "Config.h"
#include <iostream>
#include <fstream>

void Config::read_instance(const string& instance_name){
    ifstream fp;

    fp.open(instance_name);

    if(!fp.is_open()){
        cout << "Nao foi possivel abrir o arquivo\n";
        return;
    }

    fp >> dimension;

    distance_matrix.resize(dimension);
    for(int i = 0; i < dimension; i++){
        distance_matrix[i].resize(dimension);
    }
    
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            fp >> distance_matrix[i][j];
        }
    }

    fp >> depot;

    int n;
    fp >> n;//quantity of customers
    customers.resize(n);
    for(int i = 0; i < n; i++){
        fp >> customers[i];
    }

    fp.close();
}

void Config::fill_adj_matrix(){
    for(int i = 0; i < dimension; i++){
        vector<pair<int, double>> aux;
        //cout << "Criando a adjacencia do vertice " << i << ":" << endl;
        for(int j = 0; j < dimension; j++){
            if(distance_matrix[i][j]){
                //cout << "Adicionei o vertice " << j << endl;
                aux.push_back(make_pair(j, distance_matrix[i][j]));
            }
        }
        adj_matrix.push_back(aux);
    }
}

Config::Config(const string& instance_name, const int& decision_epoch_horizon){
    read_instance(instance_name);
    fill_adj_matrix();
}

void Config::print_distance_matrix(){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            cout << distance_matrix[i][j] << " ";
        }cout << endl;
    }
}

void Config::print_adj_matrix(){
    for(int i = 0; i < dimension; i++){
        cout << "Vertex [" << i << "]: ";
        for(int j = 0; j < adj_matrix[i].size(); j++){
            cout << "(" << adj_matrix[i][j].first << ", " << adj_matrix[i][j].second << ")";
            cout << ((j == (adj_matrix[i].size() - 1)) ? ("\n") : (", "));
        }
    }
}