#include <iostream>
#include <fstream>
#include <vector>
#include "../B2/car_dealer.h"

using namespace std;

// Implement read_results_from_file(std::string filename) here

vector<Order> read_results_from_file(string filename) {
    ifstream input_file(filename);
    vector<Order> orders;

    if (input_file.is_open()) {
        string buyer, manufacturer, series;
        string engine, price_str, received_str;
        double price;
        bool received;

        while (input_file >> buyer >> manufacturer >> series >> engine >> price_str >> received_str) {
            price = stod(price_str);
            received = (received_str == "1");
            orders.emplace_back(buyer, manufacturer, series, engine, price, received);
        }

        input_file.close();
    }

    return orders;
}


int main(){
    auto results = read_results_from_file("result_test_file.txt");
    for(auto result : results){
        cout << result << endl;
    }
    return 0;
}

