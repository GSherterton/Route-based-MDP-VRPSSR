#include "Config.h"
#include <iostream>
#include <fstream>

void Config::add_request(const int& index, const int& time){
    requests.push_back(make_pair(index, time));
}

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

Config::Config(){}

Config::Config(const string& instance_name, const int& decision_epoch_horizon){
    read_instance(instance_name);
    fill_adj_matrix();

    request_index = 0;

    //inicializar os requests manualmente com o index do customer
    add_request(0, 0);
    add_request(1, 0);
    add_request(4, 1);
    add_request(5, 2);
    add_request(2, 2);
    add_request(7, 4);
    add_request(8, 8);
    add_request(6, 11);
    add_request(3, 20);

    //inicializar os requests manualmente com a posicao do customer
    /*add_request(costumer[0], 0);
    add_request(costumer[1], 0);
    add_request(costumer[4], 1);
    add_request(costumer[5], 2);
    add_request(costumer[2], 2);
    add_request(costumer[7], 4);
    add_request(costumer[8], 8);
    add_request(costumer[6], 11);
    add_request(costumer[3], 20);*/
}

//the aux will be the requests revealed to the problem
vector<int> Config::receive_requests(const int& time){
    vector<int> aux;

    for(int i = request_index; i < requests.size(); i++){
        //if have a request set the customer as requested
        if(requests[i].second <= time){
            aux.push_back(requests[i].first);
        }else{
            //if the time of the request passed the actual time actualize the index of requests
            request_index = i;
            return aux;
        }
    }

    return vector<int>();
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