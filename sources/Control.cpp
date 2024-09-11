#include "Control.h"

void Control::add_request(const int& index, const int& time){
    requests.push_back(make_pair(index, time));
}

Control::Control(const string& instance_name, const int& decision_epoch_horizon){
    this->instance_name = instance_name;
    this->decision_epoch_horizon = decision_epoch_horizon;
    
    request_index = 0;
    total_reward = 0;
    
    //initialize the config
    config = Config(instance_name, decision_epoch_horizon);
    //initialize the state
    state = State(config);

    //inicializar os requests manualmente com o index do customer
    add_request(0, 0);
    add_request(1, 0);
    add_request(4, 1);
    add_request(5, 2);
    add_request(2, 2);
    add_request(7, 4);
    add_request(8, 8);
    add_request(6, 11);
    add_request(3, 20);

    //inicializar os requests manualmente com a posicao do customer
    /*add_request(costumer[0], 0);
    add_request(costumer[1], 0);
    add_request(costumer[4], 1);
    add_request(costumer[5], 2);
    add_request(costumer[2], 2);
    add_request(costumer[7], 4);
    add_request(costumer[8], 8);
    add_request(costumer[6], 11);
    add_request(costumer[3], 20);*/
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
        receive_requests(); //receive the requests

        vector<int> actual_status = state.get_status();//pega os status atuais

        cout << "Actual Requests: [";//debug if the requests are being made right
        for(int j = 0; j < config.get_customers_size(); j++){
            if(actual_status[j] == 1){
                cout << j << " ";
            }
        }cout << "]" << endl;

        //take an action
        //for now will be do nothing just pass the time
        int elapsed_time = 2;
        int new_position = 0;
        action(elapsed_time, new_position);

        //do the transition
    }
}