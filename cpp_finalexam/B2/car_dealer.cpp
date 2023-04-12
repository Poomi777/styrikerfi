#include "car_dealer.h"

using namespace std;

// Implement classes Car and Order here

Car::Car() {}

Car::Car(string manufact, string seri, double engi) :
    manufacturer(manufact), series(seri), engine(engi) {}


Car::Car(const Car& car) :
    manufacturer(car.manufacturer), series(car.series), engine(car.engine) {}

Car::~Car() {}

string Car::getManufacturer() const {
    return manufacturer;
}

string Car::getSeries() const {
    return series;
}

double Car::getEngine() const {
    return engine;
}

void Car::setManufacturer(string manufact) {
    manufacturer = manufact;
}

void Car::setSeries(string seri) {
    series = seri;
}

void Car::setEngine(double engi) {
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

string Order::getBuyer() const {
    return buyer;
}

Car Order:: getCar() const {
    return car;
}

double Order:: getPrice() const {
    return price;
}

bool Order::isReceived() const {
    return received;
}

void Order:: setBuyer(string buy) {
    buyer = buy;
}

void:: Order::setCar(const Car& carObject) {
    car = carObject;
}

void Order::setPrice(double pri) {
    price = pri;
}

void Order::setReceived(bool rec) {
    received = rec;
}

ostream& operator<<(ostream& os, const Order& order) {
    os << "Buyer: " << order.buyer << endl;
    os << "Car: " << order.car << endl;
    os << "Price: " << order.price << endl;
    os << "Received: " << (order.received ? "received" : "not received") << endl;
    return os;
}


