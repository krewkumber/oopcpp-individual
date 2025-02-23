#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stdexcept>

using namespace std;

class Car {
private:
    static int objectCount;
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
    Car(string m, int y) {
        id = nextId++;
        objectCount++;
        setModel(m);
        setYear(y);
    }

    Car(string m, int y, int w) {
        id = nextId++;
        objectCount++;
        setModel(m);
        setYear(y);
        setWeight(w);
    }

    ~Car() {
        cout << "Car with ID " << id << " destroyed.\n";
        objectCount--;
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

    static int getObjectCount() {
        return objectCount;
    }
};


int Car::objectCount = 0;
int Car::nextId = 1;

int main() {
    cout << "Running Unit Tests...\n";

    const int SIZE = 3;
    Car* cars[SIZE] = {
        new Car("Toyota Corolla", 2022, 1300),
        new Car("Honda Civic", 2018),
        new Car("Ford Mustang", 2020, 1500)
    };

    assert(cars[0]->getModel() == "Toyota Corolla");
    assert(cars[0]->getYear() == 2022);
    assert(cars[0]->getWeight() == 1300);

    assert(cars[1]->getModel() == "Honda Civic");
    assert(cars[1]->getYear() == 2018);

    assert(cars[2]->getModel() == "Ford Mustang");
    assert(cars[2]->getYear() == 2020);
    assert(cars[2]->getWeight() == 1500);

    assert(cars[0]->getId() != cars[1]->getId());
    assert(cars[1]->getId() != cars[2]->getId());

    string expectedOutput = "ID: 1, Model: Toyota Corolla, Year: 2022, Weight: 1300 kg";
    assert(cars[0]->toString() == expectedOutput);

    assert(Car::getObjectCount() == SIZE);

    cars[1]->setWeight(2200);
    assert(cars[1]->getWeight() == 2200);

    try {
        cars[1]->setWeight(6000.0);  
        assert(false);  
    } catch (const invalid_argument& e) {
        cout << "Caught invalid weight exception: " << e.what() << endl;
    }

    try {
        Car* invalidCar = new Car("Oldtimer", 1800, 1200);  
        assert(false);  
    } catch (const invalid_argument& e) {
        cout << "Caught invalid year exception: " << e.what() << endl;
    }

    for (int i = SIZE - 1; i >= 0; i--) {
        delete cars[i];
        assert(Car::getObjectCount() == SIZE - (SIZE - 1 - i)); 
    }

    cout << "All Unit Tests Passed!\n";

    return 0;
}
