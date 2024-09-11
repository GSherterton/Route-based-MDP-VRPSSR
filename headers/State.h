#pragma once
#include <iostream>
#include <vector>
#include "Config.h"

using namespace std;

class State{
    private:
        int decision_epoch;
        int position;
        int time;
        vector<int> status;
        vector<int> route_plan;
        
        //idea
        /*instead of using a vector to stores the costumers status we could have a vector
        to store the status of each vertex of the original matrix*/
        /*using this we could erase the information of a specific customer, and a costumer
        now will be just a possible location, so we'll just search if a vertex has a requested*/
        //the question is, this will descaracterize our model?
        //this will save time but use more memory

    public:
        State();
        State(const Config& config);

        inline int get_decision_epoch() const { return decision_epoch; }
        inline int get_position() const { return position; }
        inline int get_time() const { return time; }
        inline vector<int> get_status() const { return status; }
        inline vector<int> get_route_plan() const { return route_plan; }
        inline int get_route_size() const { return route_plan.size(); }

        void advance_decision_epoch() { decision_epoch++; }
        void update_position(const int& position) { this->position = position; }
        void update_route(const vector<int>& route) { this->route_plan = route; }
        void advance_time(const int& time) { this->time += time; } //adds a time to the actual time
        void set_requested(const int& request) { status[request] = 1; } //set a request to a costumer, passing the costumer index
        //void set_requested(const int& position) { status[position] = 1; } //set a request to a costumer, passing the costumer position
        void set_served(const int& customer) { status[customer] = 2; } //set a costumer to served, passing the costumer index
        //void set_served(const int& position) { status[position] = 2; } //set a costumer to served, passing the costumer position
        void update_route_plan(const vector<int>& route_plan) { this->route_plan = route_plan; }

        void update_state(const int& next_position, const vector<int>& next_route, const int& next_customer, const int& time);
};