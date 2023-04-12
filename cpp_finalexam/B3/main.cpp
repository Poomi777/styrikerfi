#include <iostream>

using namespace std;

// Implement read_results_from_file(std::string filename) here

int main(){
    auto results = read_results_from_file("result_test_file.txt");
    for(auto result : results){
        cout << result << endl;
    }
    return 0;
}
