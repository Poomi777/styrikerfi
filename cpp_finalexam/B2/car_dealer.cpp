#include "car_dealer.h"

using namespace std;

// Implement classes Car and Order here

Car::Car() {}

Car::Car(string manufact, string seri, double engi) :
    manufacturer(manufact), series(seri), engine(engi) {}


Car::Car(const Car& car) :
    manufacturer(car.manufacturer), series(car.series), engine(car.engine) {}

Car::~Car() {}

string Car::get_Manufacturer() const {
    return manufacturer;
}

string Car::get_Series() const {
    return series;
}

double Car::get_Engine() const {
    return engine;
}

void Car::set_Manufacturer(string manufact) {
    manufacturer = manufact;
}

void Car::set_Series(string seri) {
    series = seri;
}

void Car::set_Engine(double engi) {
    engine = engi;
}

ostream& operator<<(ostream& os, const Car& car) {
    os << car.manufacturer << " " << car.series << " with engine " << car.engine;
    return os;
}



Order::Order() {}

Order::Order(string buy, Car carObject, double pri, bool receive) :
    buyer(buy), car(carObject), price(pri), received(receive) {}

Order::Order(const Order& order) :
    buyer(order.buyer), car(order.car), price(order.price), received(order.received) {}

Order::~Order() {}

string Order::get_Buyer() const {
    return buyer;
}

Car Order:: get_Car() const {
    return car;
}

double Order:: get_Price() const {
    return price;
}

bool Order::isReceived() const {
    return received;
}

void Order:: set_Buyer(string buy) {
    buyer = buy;
}

void:: Order::set_Car(const Car& carObject) {
    car = carObject;
}

void Order::set_Price(double pri) {
    price = pri;
}

void Order::set_Received(bool rec) {
    received = rec;
}

ostream& operator<<(ostream& os, const Order& order) {
    os << "Buyer: " << order.buyer << endl;
    os << "Car: " << order.car << endl;
    os << "Price: " << order.price << endl;
    os << "Received: " << (order.received ? "received" : "not received") << endl;
    return os;
}


