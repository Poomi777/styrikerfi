#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Car {
    string manufacturer;
    string series;
    double engine;
};

struct Order {
    int id;
    string name;
    string phone;
    Car cars[10];
    int num_of_cars = 0;
};

void add_order(Order* orders, int& num_of_orders) {
    Order new_order;

    cout << "Enter your order name: ";
    cin >> new_order.name;
    cout << "Enter your phone number for the order: ";
    cin >> new_order.phone;

    new_order.id = num_of_orders + 1;
    orders[num_of_orders] = new_order;
    num_of_orders++;

    cout << "A new order has been added with the ID: " << new_order.id << endl;
}

void add_car(Order* orders, int num_of_orders) {
    int order_input;
    
    cout << "Enter the ID of an order: ";
    cin >> order_input;

    bool order_found = false;

    for (int i = 0; i < num_of_orders; i++) {
        if (orders[i].id == order_input) {
            order_found = true;
            Car new_car;

            cout << "Who is the manufacturer?: ";
            cin >> new_car.manufacturer;
            cout << "What is the series?: ";
            cin >> new_car.series;
            cout << "What is the engine size?: ";
            cin >> new_car.engine;

            orders[i].cars[orders[i].num_of_cars] = new_car;
            orders[i].num_of_cars++;

            cout << "Yuor car has been added to the orders with the ID: " << order_input << endl;

            break;
        }
    }

    if (!order_found) {
        cout << "Your order was not found." << endl;
    }
}

void print_order(Order* orders, int num_of_orders) {
    int order_input;
    
    cout << "What is the ID of the order you want to print?: ";
    cin >> order_input;

    bool order_found = false;

    for (int i = 0; i < num_of_orders; i++) {
        if (orders[i].id == order_input) {
            order_found = true;

            cout << "Order ID: " << orders[i].id << endl;
            cout << "Name: " << orders[i].name << endl;
            cout << "Phone: " << orders[i].phone << endl;
            cout << "Cars: " << endl;
            for (int j = 0; j < orders[i].num_of_cars; j++) {
                cout << "   Manufacturer: " << orders[i].cars[j].manufacturer << endl;
                cout << "   Series: " << orders[i].cars[j].series << endl;
                cout << "   Engine size: " << orders[i].cars[j].engine << endl << endl;
            }
            break;
            
        }
    }

    if (!order_found) {
        cout << "Your Order was not found" << endl;
    }
}

void search_order(Order* orders, int num_of_orders) {
    string search;
    bool order_found = false;

    cout << "Enter the name or phone number that you want to search for: ";
    cin >> search;

    for (int i = 0; i < num_of_orders; i++) {
        if (orders[i].name == search || orders[i].phone == search) {
            order_found = true;

            cout << "Order ID: " << orders[i].id << endl;
            cout << "Name: " << orders[i].name << endl;
            cout << "Phone: " << orders[i].phone << endl;
            cout << "Cars: " << endl;
            for (int j = 0; j < orders[i].num_of_cars; j++) {
                cout << "   Manufacturer: " << orders[i].cars[j].manufacturer << endl;
                cout << "   Series: " << orders[i].cars[j].series << endl;
                cout << "   Engine size: " << orders[i].cars[j].engine << endl << endl;
            }
        }
    }

    if (!order_found) {
        cout << "Your order was not found" << endl;
    }
}

void save_orders(Order* orders, int num_of_order) {
    ofstream file("orders.txt");
    for (int i = 0; i < num_of_order; i++) {
        file << orders[i].id << " " << orders[i].name << " " << orders[i].phone << " ";

        for (int j = 0; j < orders[i].num_of_cars; j++) {
            file << orders[i].cars[j].manufacturer << " " << orders[i].cars[j].series << " " << orders[i].cars[j].engine << " ";
        }

        file << endl;

    }

    file.close();
}

void load_orders(Order* orders, int& num_of_orders) {
    ifstream file("orders.txt");
    if (file) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Order new_order;
            ss >> new_order.id >> new_order.name >> new_order.phone;
            while (ss) {
                Car new_car;
                ss >> new_car.manufacturer >> new_car.series >> new_car.engine;
                if (ss) {
                    new_order.cars[new_order.num_of_cars] = new_car;
                    new_order.num_of_cars++;
                }
            }
            orders[num_of_orders] = new_order;
            num_of_orders++;
        }
        cout << "Loaded " << num_of_orders << " orders from file" << endl;
    } else {
        cout << "No saved data detected to load from" << endl;
    }
    file.close();
}

int main(){

    Order orders[100];
    int num_of_orders = 0;

    load_orders(orders, num_of_orders);
    bool quit = false;

    while (!quit) {
        int choice;

        cout << "What would you like to do:" << endl;
        cout << "1. Create new order" << endl;
        cout << "2. Add a car to order" << endl;
        cout << "3. Print a specific order" << endl;
        cout << "4. Search for an order" << endl;
        cout << "5. Quit and save" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                add_order(orders, num_of_orders);
                break;

            case 2:
                add_car(orders, num_of_orders);
                break;
            
            case 3:
            print_order(orders, num_of_orders);
            break;

            case 4:
            search_order(orders, num_of_orders);
            break;

            case 5:
                quit = true;
                save_orders(orders, num_of_orders);
                cout << "Saved " << num_of_orders << " orders to file" << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
                break;

        }

    }

    return 0;
}
