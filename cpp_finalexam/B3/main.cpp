#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../../B2/car_dealer.h"

using namespace std;

// Implement read_results_from_file(std::string filename) here

vector<Order> read_results_from_file(const string& filename) {
    ifstream file(filename);
    vector<Order> results;

    if (!file.is_open()) {
        cerr << "File could not be opend: " << filename << endl;
        return results;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string buyer, manufacturer, series;
        double engine, price;
        int received_int;
        bool received;

        ss >> buyer >> manufacturer >> series >> engine >> price >> received_int;
        received = received_int == 1;

        Car car(manufacturer, series, engine);
        Order order(buyer, car, price, received);
        results.push_back(order);
    }

    file.close();
    return results;
}


int main(){
    auto results = read_results_from_file("result_test_file.txt");
    for(auto result : results){
        cout << result << endl;
    }
    return 0;
}
