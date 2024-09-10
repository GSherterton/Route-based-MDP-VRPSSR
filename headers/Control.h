#pragma once
#include "Config.h"
#include "State.h"
#include <vector>

using namespace std;

class Control{
    private:
        int decision_epoch_horizon;
        string instance_name;
        Config config;
        State state;

        int request_index;
        vector<pair<int, int>> requests;//costumer, time of the request

        int total_reward;

        void receive_requests();
    public:
        Control(const string& instance_name, const int& decision_epoch_horizon);
        void initiate();
};
