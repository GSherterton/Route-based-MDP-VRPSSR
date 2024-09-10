#include "Control.h"

Control::Control(const string& instance_name, const int& decision_epoch_horizon){
    this->instance_name = instance_name;
    this->decision_epoch_horizon = decision_epoch_horizon;
    
    request_index = 0;
    
    //initialize the config
    config = Config(instance_name, decision_epoch_horizon);
    //initialize the state
    state = State(config);
}

void Control::receive_requests(){
    for(int i = request_index; i < requests.size(); i++){
        //if have a request set the customer as requested
        if(requests[i].second <= state.get_time()){
            state.set_requested(requests[i].first);
        }else{
            //if the time of the request passed the actual time actualize the index of requests
            request_index = i;
            return;
        }
    }
}

void Control::initiate(){
    //iterates above the decision epoch horizon
    for(int i = 0; i < decision_epoch_horizon; i++){
        receive_requests(); //receive the requests
        //take an action
        //do the transition
    }
}