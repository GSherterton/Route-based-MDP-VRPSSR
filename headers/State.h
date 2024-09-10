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
        
    public:
        State(const Config& config); //talvez não precise passar a config como parametro

        inline int get_decision_epoch() const { return decision_epoch; }
        inline int get_position() const { return position; }
        inline int get_time() const { return time; }
        inline vector<int> get_status() const { return status; }
        inline vector<int> get_route_plan() const { return route_plan; }

        void set_requested(const int& request) { status[request] = 1; }
};