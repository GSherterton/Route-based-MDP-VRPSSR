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
        
    public:
        State(const Config& config); //talvez não precise passar a config como parametro

        inline int get_decision_epoch() const { return decision_epoch; }
        inline int get_time() const { return time; }
        inline int get_position() const { return position; }
        inline vector<int> get_status() const { return status; }
};