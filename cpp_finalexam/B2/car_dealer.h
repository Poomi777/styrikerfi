#ifndef CAR_DEALER_H_987234
#define CAR_DEALER_H_987234

#include <iostream>
#include <string>

using namespace std;

// Define classes Car and Order here
class Car{
    private:
    string manufacturer = "";
    string series = "";
    double engine = 0.0;

    public: 
        Car();
        Car(string manufact, string seri, double engi);
        Car(const Car& car);
        ~Car();

        string get_manufacturer() const;
        string get_series() const;
        double get_engine() const;

        void set_manufacturer(string manufact);
        void set_series(string seri);
        void set_engine(double engi);

        friend ostream& operator<<(ostream& os, const Car& car);
};

class Order {
    private:
        string buyer = "";
        Car car;
        double price = 0.0;
        bool received = false;

    public:
    Order();
    Order(string buy, Car carObject, double pri, bool receive);
    Order(const Order& order);
    ~Order();

    string get_buyer() const;
    Car get_car() const;
    double get_price() const;
    bool isReceived() const;

    void set_buyer(string buy);
    void set_car(const Car& carObject);
    void set_price(double pri);
    void set_received(bool receive);

    friend ostream& operator<<(ostream& os, const Order& order);
};


#endif //CAR_DEALER_H_987234
