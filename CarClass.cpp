#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Car {
private:
    static int count;  
    static int nextId;  

    int id;
    string model;
    int year;
    double weight;

    void setModel(const string& m) {
        model = m;
    }

    void setYear(int y) {
        if (y >= 1886 && y <= 2025) { 
            year = y;
        } else {
            throw 1;
        }
    }

    void setWeight(double w) {
        if (w >= 500 && w <= 5000) { 
            weight = w;
        } else {
            throw 1;
        }
    }

public:
    // Constructor with model and year
    Car(string m, int y) {
        id = nextId++;
        count++;
        setModel(m);
        setYear(y);
        weight = 1200.0; // Default weight
    }

    // Constructor with all parameters
    Car(string m, int y, double w) {
        id = nextId++;
        count++;
        setModel(m);
        setYear(y);
        setWeight(w);
    }

    ~Car() {
        cout << "Car with ID " << id << " destroyed.\n";
        count--; 
    }

    string getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }

    double getWeight() const {
        return weight;
    }

    int getId() const {
        return id;
    }

    string toString() const {
        stringstream ss;
        ss << "ID: " << id << ", Model: " << model << ", Year: " << year << ", Weight: " << weight << " kg";
        return ss.str();
    }

    static int getCount() {
        return count;
    }
};


int Car::count = 0;
int Car::nextId = 1; 

int main() {
    try {
        Car car1("Toyota Corolla", 2022, 1300.5);
        cout << car1.toString() << "\n";

        Car car2("Honda Civic", 2018);
        cout << car2.toString() << "\n";

        cout << "Total Cars Currently Active: " << Car::getCount() << "\n";

        {
            Car tempCar("Temporary Car", 2020, 1500.0);
            cout << tempCar.toString() << "\n";
            cout << "Total Cars Currently Active: " << Car::getCount() << "\n";
        } // tempCar goes out of scope and is destroyed here

        cout << "Total Cars Currently Active: " << Car::getCount() << "\n";

    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
