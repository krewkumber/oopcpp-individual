#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Car {
private:
    static int count;
    int id;
    string model;
    int year;
    double weight;

public:
    // Constructor
    Car(string m, int y, double w) : model(m), year(y), weight(w) {
        id = ++count;
    }

    // Destructor
    ~Car() {
        cout << "Car with ID " << id << " destroyed.\n";
    }

    // Getter methods
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

    // Setter methods
    void setModel(const string& m) {
        model = m;
    }
    
    void setYear(int y) {
        year = y;
    }
    
    void setWeight(double w) {
        weight = w;
    }

    // toString method using stringstream
    string toString() const {
        stringstream ss;
        ss << "ID: " << id << ", Model: " << model << ", Year: " << year << ", Weight: " << weight << " kg";
        return ss.str();
    }

    // Display method
    void display() const {
        cout << toString() << "\n";
    }

    // Static method to get count
    static int getCount() {
        return count;
    }
};

int Car::count = 0;

int main() {
    Car myCar("Toyota Corolla", 2022, 1300.5);
    myCar.display();
    cout << "Total Cars Created: " << Car::getCount() << "\n";
    return 0;
}
