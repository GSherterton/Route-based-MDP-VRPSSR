#pragma once
#include "Config.h"
#include "State.h"
#include <vector>

using namespace std;

class Control{
    private:
        string instance_name;
        int decision_epoch_horizon;
        Config config;
        State state;

        int request_index;
        vector<pair<int, int>> requests;//costumer index, time of the request
        //vector<pair<int, int>> requests;//costumer position, time of the request

        int total_reward;

        void add_request(const int& index, const int& time);
        void receive_requests();
        void action(const int& elapsed_time, const int& new_position);
    public:
        Control(const string& instance_name, const int& decision_epoch_horizon);
        void initiate();
};
