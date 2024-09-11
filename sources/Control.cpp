#include "Control.h"

Control::Control(const string& instance_name, const int& decision_epoch_horizon){
    this->instance_name = instance_name;
    this->decision_epoch_horizon = decision_epoch_horizon;
    
    total_reward = 0;
    
    //initialize the config
    config = Config(instance_name, decision_epoch_horizon);
    //initialize the state
    state = State(config);
}

void Control::insert_new_requests(const vector<int>& new_requests){
    requests.insert(requests.end(), new_requests.begin(), new_requests.end()); //insert the new requests in the total requests
    // for(int i = 0; i < new_requests.size(); i++){
    //     requests.push_back(new_requests[i]);
    // }
}

//update the status of the new requests received in that decision epoch
void Control::update_status(const vector<int>& new_requests){
    for(int i = 0; i < new_requests.size(); i++){
        state.set_requested(new_requests[i]);
    }
}

void Control::action(const int& elapsed_time, const int& new_position){
    state.advance_decision_epoch();


    state.update_position(state.get_position());//the position remains the same
    state.advance_time(elapsed_time);
    //no set request
    total_reward += 0;//has to update the total reward
}

void Control::initiate(){
    //iterates above the decision epoch horizon
    for(int i = 0; i < decision_epoch_horizon; i++){
        vector<int> new_requests;
        new_requests = config.receive_requests(state.get_time()); //receive the new requests

        update_status(new_requests); //update the status of the new requests

        insert_new_requests(new_requests);

        cout << "Actual Requests: [";//debug if the requests are being made right
        int j = 0;
        for(auto it : requests){
            cout << it << ((j++ == requests.size()-1) ? ("") : (" "));
        }cout << "]" << endl;
        // for(int j = 0; j < requests.size(); j++){
        //     cout << requests[j] << ((j == requests.size()-1) ? ("") : (" "));
        // }cout << "]" << endl;

        


        //take an action
        //for now will be do nothing just pass the time
        int elapsed_time = 2;
        int new_position = 0;
        action(elapsed_time, new_position);

        //do the transition
    }
}