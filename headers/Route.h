#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Route{
    public:
        vector<int> path;   //the vertices of the route
        double obj = 0;     //the objective value of the route

        void print_route(){
            int n = path.size();

            if(n == 0){
                cout << "The route is empty!\n";
            }else{
                cout << "Objective Value: " << obj << endl;
                cout << "Path: [";
                for(int i = 0; i < path.size(); i++){
                    cout << path[i] << ((i == n-1) ? ("") : (", "));
                }
                cout << "]\n";
            }
        }
};