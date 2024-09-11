#include "State.h"

State::State(){}

//o estado inicial começa na decision_epoch 0, no depot, com o
//tempo zerado e com os status todos zerados
State::State(const Config& config){
    decision_epoch = 0;
    position = config.get_depot();
    time = 0;
    status = vector<int>(config.get_customers_size(), 0); //customer status
    //status = vector<int>(config.get_dimension(), 0); //vertex status
}

void State::update_state(const int& next_position, const vector<int>& next_route, const int& next_customer, const int& time){
    advance_decision_epoch();
    update_position(next_position);
    update_route(next_route);
    set_served(next_customer);
    advance_time(time);
}