#include <iostream>
#include <fstream>
#include <vector>
#include "../B2/car_dealer.h"

using namespace std;

// Implement read_results_from_file(std::string filename) here

vector<Order> read_results_from_file(string filename) {
    ifstream input_file(filename);
    vector<Order> results;

    if (input_file.is_open()) {
        string buyer, manufacturer, series;
        string engine_str, price_str, received_str;
        double engine, price;
        bool received;

        while (input_file >> buyer >> manufacturer >> series >> engine_str >> price_str >> received_str) {
            engine =  stod(engine_str);
            price = stod(price_str);
            received = (received_str == "1");
            Car car(manufacturer, series, engine);
            results.emplace_back(buyer, car, price, received);
        }

        input_file.close();
    }

    return results;
}


int main(){
    auto results = read_results_from_file("result_test_file.txt");
    for(auto result : results){
        cout << result << endl;
    }
    return 0;
}
