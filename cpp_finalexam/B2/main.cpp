#include <iostream>

#include "car_dealer.h"
using namespace std;

void test_car(){
    Car c1("toyota", "terrain", 2.1);
    cout << c1 << endl;
    Car c2(c1);
    cout << c2 << endl;
    Car c3;
    cout << c3 << endl;
    c3 = c1;
    cout << c3 << endl;
}

void test_order(){
    Car c1("toyota", "terrain", 2.1);
    Order o1("Kari", c1, 2100000, 0);
    Order o2("Arnar", Car("fiat", "uno", 0.8), 1300000.0, 1);
    cout << o1 << endl;
    cout << o2 << endl;
    cout << "Buyer1: " << o1.get_buyer() << endl;
    cout << "Car1: " << o1.get_car() << endl;
    cout << "Price1: " << o1.get_price() << endl;
    if(o1.get_received()){
        cout << "Order 1 received" << endl;
    }
    else{
        cout << "Order 1 not received" << endl;
    }
    cout << "Buyer2: " << o2.get_buyer() << endl;
    cout << "Car2: " << o2.get_car() << endl;
    cout << "Price2: " << o2.get_price() << endl;
    if(o2.get_received()){
        cout << "Order 2 received" << endl;
    }
    else{
        cout << "Order 2 not received" << endl;
    }
    Order o3;
    cout << o3 << endl;
    o3.set_buyer("Fridrik");
    o3.set_car(Car("Mercedes", "Benz", 2.0));
    o3.set_price(63000000);
    o3.set_received(0);
    cout << o3 << endl;
    Order o4(o2);
    cout << o4 << endl;
}

int main(){
    test_car();
    test_order();
}
