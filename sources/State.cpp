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