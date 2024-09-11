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
}

//update the status of the new requests received in that decision epoch
void Control::update_status(const vector<int>& new_requests){
    for(int i = 0; i < new_requests.size(); i++){
        state.set_requested(new_requests[i]);
    }
}

void Control::receive_requests(){
    vector<int> new_requests;
    new_requests = config.receive_requests(state.get_time());

    update_status(new_requests); //update the status of the new requests

    insert_new_requests(new_requests);

    cout << "Actual Requests: [";//debug if the requests are being made right
    int j = 0;
    for(auto it : requests){
        cout << it << ((j++ == requests.size()-1) ? ("") : (" "));
    }cout << "]" << endl;
}

void Control::action(){
    int next_customer = -1; //stores the next customer
    vector<int> new_route; //stores the list of next customers

    int reward = 0;
    
    int i = 0;
    for(auto it : requests){
        if(i == 0){
            next_customer = it;
        }else{
            new_route.push_back(it);
        }
        i++;
    }
    
    //the config get_position returns the position of a given custormer's index
    //and the state get_position returns the position of the actual state
    int next_position = ((next_customer != -1) ? (config.get_position(next_customer)) : (state.get_position()));

    // if(next_customer != -1){
    //     next_position = config.get_position(next_customer);
    // }

    //have a new request and the car wont stay stopped
    if(next_position != state.get_position()){
        reward += 1;
        requests.pop_front();
    }

    //adds the difference between the new and old route
    reward += (new_route.size() - state.get_route_size());

    //update the total_reward
    total_reward += reward;

    int time = 2; //calcular o tempo de chegar no proximo customer

    //update the state
    state.update_state(next_position, new_route, next_customer, time);
}

void Control::initiate(){
    //iterates above the decision epoch horizon
    for(int i = 0; i < decision_epoch_horizon; i++){
        //receive the new requests
        receive_requests();

        //take an action
        action();


        //do the transition
        //the trasition is inside the action()
    }
}