#include <iostream>
#include "data_processing.h"

void process_stuff(int my_number, DataStore &ds){
    std::cout << "Processor #" << my_number << " starting" << std::endl;
    while(!ds.is_empty()){
        DataPart dp = ds.get_next();
        std::cout << "Processor #" << my_number << " processing data: " << dp << std::endl;
        int result = DataProcessing::process(dp);
        std::cout << "Processor #" << my_number << " RESULT: " << result << std::endl;
    }
    std::cout << "Processor #" << my_number << " STOPPING" << std::endl;
}

int main(){
    DataStore ds;

    process_stuff(1, ds);

    return 0;
}
