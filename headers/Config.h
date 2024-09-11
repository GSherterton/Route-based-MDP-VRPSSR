#pragma once
#include <vector>
#include <string>

using namespace std;

class Config{
    private:
        int decision_epoch_horizon;
        int dimension;
        vector<vector<double>> distance_matrix;
        vector<vector<pair<int, double>>> adj_matrix;

        int depot; //stores where the depot is located
        vector<int> customers; //stores the position of each customer

        int request_index;
        vector<pair<int, int>> requests;//costumer index, time of the request
        //vector<pair<int, int>> requests;//costumer position, time of the request

        void add_request(const int& index, const int& time);
        //void add_request(const int& position, const int& time);

        void read_instance(const string& instance_name);
        void fill_adj_matrix();
    public:
        Config();
        Config(const string& instance_name, const int& decision_epoch_horizon);

        vector<int> receive_requests(const int& time); //returns the new requests

        //debug functions
        void print_distance_matrix();
        void print_adj_matrix();
        
        inline int get_decision_epoch_horizon() const { return decision_epoch_horizon; }
        inline int get_distance(const int& i, const int& j) const { return distance_matrix[i-1][j-1]; }
        inline int get_dimension() const { return dimension; }
        inline int get_depot() const { return depot; }
        inline int get_position(const int& customer) const { return customers[customer]; }
        inline int get_customers_size() const { return customers.size(); }
};