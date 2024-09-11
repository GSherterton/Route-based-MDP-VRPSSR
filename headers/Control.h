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

        //faz mais sentido os requests de control serem apenas os revelados
        vector<int> requests;//costumer index
        //vector<int> requests;//costumer position

        int total_reward;

        // void update_status(const vector<int>& new_requests);
        void action(const int& elapsed_time, const int& new_position);
    public:
        Control(const string& instance_name, const int& decision_epoch_horizon);
        void initiate();
};
