#include <iostream>
#include <string>
using namespace std;

class User {
public:
    string name;
    string licenseType;
    int userID;

    User(string n, string l, int id) : name(n), licenseType(l), userID(id) {}

    string getLicense() { return licenseType; }
    string getName() { return name; }
    int getID() { return userID; }
};

class Vehicle {
public:
    string model;
    string eligibleLicense;

    Vehicle(string m, string license) : model(m), eligibleLicense(license) {}

    bool canRent(string userLicense) {
        return userLicense == eligibleLicense;
    }

    string getModel() { return model; }
};

class RentalSystem {
public:
    User* users[10];
    Vehicle* vehicles[10];
    int userCount = 0;
    int vehicleCount = 0;

    void registerUser(string name, string license, int id) {
        users[userCount++] = new User(name, license, id);
    }

    void addVehicle(string model, string license) {
        vehicles[vehicleCount++] = new Vehicle(model, license);
    }

    void showVehicles() {
        cout << "\nAvailable Vehicles:\n";
        for (int i = 0; i < vehicleCount; i++) {
            cout << vehicles[i]->getModel() << " (License: " << vehicles[i]->eligibleLicense << ")\n";
        }
    }

    void rentVehicle(int userID, string vehicleModel) {
        User* user = nullptr;
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getID() == userID) {
                user = users[i];
                break;
            }
        }

        if (!user) {
            cout << "User not found!\n";
            return;
        }

        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->getModel() == vehicleModel) {
                if (vehicles[i]->canRent(user->getLicense())) {
                    cout << user->getName() << " rented " << vehicleModel << " successfully!\n";
                } else {
                    cout << user->getName() << " is not eligible to rent " << vehicleModel << ".\n";
                }
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }
};

int main() {
    RentalSystem system;

    system.registerUser("Alice", "Full", 101);
    system.registerUser("Bob", "Learner", 102);

    system.addVehicle("Toyota Corolla", "Full");
    system.addVehicle("Yamaha R15", "Learner");

    system.showVehicles();

    system.rentVehicle(101, "Toyota Corolla");  // Alice can rent
    system.rentVehicle(102, "Toyota Corolla");  // Bob can't rent
    system.rentVehicle(102, "Yamaha R15");     // Bob can rent

    return 0;
}

