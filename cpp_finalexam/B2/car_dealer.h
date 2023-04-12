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

        string get_Manufacturer() const;
        string get_Series() const;
        double get_Engine() const;

        void set_Manufacturer(string manufact);
        void set_Series(string seri);
        void set_Engine(double engi);

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

    string get_Buyer() const;
    Car get_Car() const;
    double get_Price() const;
    bool isReceived() const;

    void set_Buyer(string buy);
    void set_Car(const Car& carObject);
    void set_Price(double pri);
    void set_Received(bool receive);

    friend ostream& operator<<(ostream& os, const Order& order);
};


#endif //CAR_DEALER_H_987234
