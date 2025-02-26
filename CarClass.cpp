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
    static int minWeight;
    static int maxWeight;

    int id;
    string model;
    int year;
    int weight;

public:
    Car(string m, int y) {
        id = nextId++;
        objectCount++;
        try {
            setModel(m);
            setYear(y);
        } catch (...) {  
            objectCount--; 
            throw; 
        }
    }

    Car(string m, int y, int w) : Car(m, y) {
        try {
        setWeight(w);
        }

        catch (...) {  
        objectCount--; 
        throw; 
        }
    }

    ~Car() {
        objectCount--;
    }

private:
    void setModel(const string& m) {
        model = m;
    }

    void setYear(int y) {
        if (y >= 1886) {
            year = y;
        } else {
            throw invalid_argument("Year must be 1886 or greater");
        }
    }

public:
    void setWeight(int w) {
        if (w >= minWeight && w <= maxWeight) {
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
        ss << id << "," << model << "," << year << "," << weight;
        return ss.str();
    }

    static int getObjectCount() {
        return objectCount;
    }
};


int Car::objectCount = 0;
int Car::nextId = 0;
int Car::minWeight = 500;
int Car::maxWeight = 5000;

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

    string expectedOutput = "0,Toyota Corolla,2022,1300";
    assert(cars[0]->toString() == expectedOutput);

    assert(Car::getObjectCount() == SIZE);

    cars[1]->setWeight(2200);
    assert(cars[1]->getWeight() == 2200);

    try {
        cars[1]->setWeight(6000.0);  
        assert(false);  
    } catch (const invalid_argument& e) {
        cout << "Caught invalid argument exception: " << e.what() << endl;
    }

    try {
        Car* invalidCar = new Car("Oldtimer", 1800, 1200);  
        assert(false);  
    } catch (const invalid_argument& e) {
        cout << "Caught invalid argument exception: " << e.what() << endl;
    }


    for (int i = SIZE - 1; i >= 0; i--) {
        delete cars[i];
        assert(Car::getObjectCount() == SIZE - (SIZE - i)); 
    }

    assert(Car::getObjectCount() == 0);

    cout << "All Unit Tests Passed!\n";

    return 0;
}
