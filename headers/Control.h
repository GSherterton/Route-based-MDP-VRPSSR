#pragma once
#include "Config.h"
#include "State.h"
#include <vector>
#include <list>

using namespace std;

class Control{
    private:
        string instance_name;
        int decision_epoch_horizon;
        Config config;
        State state;

        //faz mais sentido os requests de control serem apenas os revelados
        list<int> requests;//costumer index
        //list<int> requests;//costumer position

        int total_reward;

        void insert_new_requests(const vector<int>& new_requests);
        void update_status(const vector<int>& new_requests);
        void receive_requests();
        void action();
    public:
        Control(const string& instance_name, const int& decision_epoch_horizon);
        void initiate();
};
