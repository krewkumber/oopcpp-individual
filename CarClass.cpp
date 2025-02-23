#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <memory>

using namespace std;

class Car {
private:
    static int count;  
    static int nextId;  

    int id;
    string model;
    int year;
    int weight;

    void setModel(const string& m) {
        model = m;
    }

    void setYear(int y) {
        if (y >= 1886 && y <= 2025) { 
            year = y;
        } else {
            throw invalid_argument("Year must be between 1886 and 2025.");
        }
    }

public:
    // Constructor with model and year
    Car(string m, int y) {
        id = nextId++;
        count++;
        setModel(m);
        setYear(y);
    }

    // Constructor with all parameters
    Car(string m, int y, int w) {
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

    void setWeight(int w) {
        if (w >= 500 && w <= 5000) { 
            weight = w;
        } else {
            throw invalid_argument("Weight must be between 500 and 5000 kg.");
        }
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
    cout << "Running Unit Tests...\n";

    // Step 1: Create a fixed-size array of Car pointers (without default weight)
    const int SIZE = 3;
    Car* cars[SIZE] = {
        new Car("Toyota Corolla", 2022, 1300),
        new Car("Honda Civic", 2018, 1400),
        new Car("Ford Mustang", 2020, 1500)
    };

    // Step 2: Test Getters (Indirectly Tests Private Setters)
    assert(cars[0]->getModel() == "Toyota Corolla");
    assert(cars[0]->getYear() == 2022);
    assert(cars[0]->getWeight() == 1300);

    assert(cars[1]->getModel() == "Honda Civic");
    assert(cars[1]->getYear() == 2018);
    assert(cars[1]->getWeight() == 1400);

    assert(cars[2]->getModel() == "Ford Mustang");
    assert(cars[2]->getYear() == 2020);
    assert(cars[2]->getWeight() == 1500);

    // Step 3: Test ID Uniqueness
    assert(cars[0]->getId() != cars[1]->getId());
    assert(cars[1]->getId() != cars[2]->getId());

    // Step 4: Test Object Counter
    assert(Car::getCount() == SIZE);

    // Step 5: Test Public Setter (`setWeight`)
    cars[0]->setWeight(2200);
    assert(cars[0]->getWeight() == 2200);

    // Step 6: Test Invalid Values Throw Exceptions
    try {
        cars[1]->setWeight(6000.0);  // Invalid weight
        assert(false);  // Should not reach here
    } catch (const invalid_argument& e) {
        cout << "Caught invalid weight exception: " << e.what() << endl;
    }

    try {
        Car* invalidCar = new Car("Oldtimer", 1800, 1200);  // Invalid year
        assert(false);  // Should not reach here
    } catch (const invalid_argument& e) {
        cout << "Caught invalid year exception: " << e.what() << endl;
    }

    // Step 7: Delete objects and verify count decreases
    for (int i = 0; i < SIZE; i++) {
        delete cars[i];
        cars[i] = nullptr;
        assert(Car::getCount() == SIZE - (i + 1));
    }

    cout << "All Unit Tests Passed!\n";

    return 0;
}
