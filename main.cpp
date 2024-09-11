#include <iostream>
#include <vector>
#include "Control.h"

using namespace std;

static int K = 7; //decision epoch horizon

int main(int argc, char** argv){
    //in the conventional model for VRPSSR
    /*k- a decision epoch occurs when the vehicle arrives at a location and observers new customer requests.*/
    /*the current state sk at decision epoch k includes nk- the vehicle's current location, tk- time of arrival,
    and zk- a vector of status(0- not requested, 1- requested but not serviced, 2- serviced) at time tk*/
    /*xk- an action at an epoch k is go to a customer with status 1 or back to the depot, subject to that the
    actual time + the time to the customer + the time from costumer to depot will be lower than the total time*/
    /*when a decision is taken an reward is accrued if a decision moves the vehicle to a location where service
    has been requested*/
    /*the trasition from a action xk is a post-decision state, where the new nk is the xk of the action, the new
    tk is the old tk + the distance from old nk to the new nk, and the status of the old nk if is a costumer, is
    set to 2*/
    /*the objective function is to maximize the expected sum of rewards across the decision epochs*/

    //in the route based model
    /*same decision epoch*/
    /*the state now have the old state more the actual route plan, the initial route is empty*/
    /*an action now have the old action more the new route plan*/
    /*the new reward, called marginal reward is the old reward more the diference between customers in the old to
    new route plan*/

    /*in the article example there is a matrix in which each edge is equal to 10 and each vertex is connected to another
    in only four directions like an plus signal*/

    //  the article matrix
    // {{ 0,  1,  2,  3,  4},
    //  { 5,  6,  7,  8,  9},
    //  {10, 11, 12, 13, 14},
    //  {15, 16, 17, 18, 19},
    //  {20, 21, 22, 23, 24}}

    if(argc < 2){//at least the instance name is needed
        cout << "Missing parameters!\n";

        return -1;
    }

    //initialize the control passing the instance name and with decision_epoch_horizon
    Control control = Control(argv[1], K);
    control.initiate();

    // //creates and read the distance matrix
    // vector<double> distance_matrix;
    // distance_matrix read(instance_name);

    // //creates and fill the adjacency matrix
    // vector<vector<pair<int, double>>> adj_matrix; 
    // fill_adj(adj_matrix, distance_matrix);


    //Config config = Config(K, distance_matrix);

    // for(int k = 0; k <= config.get_decision_epoch_horizon(); k++){//iterates at each decision epoch
        
    // }


    return 0;
}