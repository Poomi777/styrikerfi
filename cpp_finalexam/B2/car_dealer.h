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

        string getManufacturer() const;
        string getSeries() const;
        double getEngine() const;

        void setManufacturer(string manufact);
        void setSeries(string seri);
        void setEngine(double engi);

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

    string getBuyer() const;
    Car getCar() const;
    double getPrice() const;
    bool isReceived() const;

    void setBuyer(string buy);
    void setCar(const Car& carObject);
    void setPrice(double pri);
    void setReceived(bool receive);

    friend ostream& operator<<(ostream& os, const Order& order);
};


#endif //CAR_DEALER_H_987234
