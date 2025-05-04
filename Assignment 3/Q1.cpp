#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#define MAX_SEATS 60
#define MAX_VEHICLES 10
#define MAX_USERS 20

class PaymentPendingException : public exception {
    const char* what() const noexcept override {
        return "Booking failed: payment not received.";
    }
};

class AlreadyBookedException : public exception {
    const char* what() const noexcept override {
        return "This seat has already been reserved.";
    }
};

class UserTypeConflictException : public exception {
    const char* what() const noexcept override {
        return "Booking error: seat is restricted to a different user type.";
    }
};

class Seat {
public:
    int seatNum;
    string allowedUserType;
    bool booked;

    Seat() : seatNum(0), allowedUserType(""), booked(false) {}
    Seat(int num, string type) : seatNum(num), allowedUserType(type), booked(false) {}
};

class Route;
class Vehicle;

class User {
public:
    string userID, fullName, emailAddress;
    bool hasCompletedPayment;

    User() {}
    User(string id, string name, string email, bool paid)
        : userID(id), fullName(name), emailAddress(email), hasCompletedPayment(paid) {}

    virtual string getUserType() const = 0;
    virtual int calculateFare(bool acEnabled) const = 0;
};

class Student : public User {
public:
    Student() {}
    Student(string id, string name, string email, bool paid)
        : User(id, name, email, paid) {}

    string getUserType() const override { return "Student"; }

    int calculateFare(bool acEnabled) const override {
        return acEnabled ? 7000 : 5000;
    }
};

class Faculty : public User {
public:
    Faculty() {}
    Faculty(string id, string name, string email, bool paid)
        : User(id, name, email, paid) {}

    string getUserType() const override { return "Faculty"; }

    int calculateFare(bool acEnabled) const override {
        return acEnabled ? 5000 : 3000;
    }
};

class Route {
public:
    string origin, destination;
    int totalDistance;

    Route() {}
    Route(string start, string end, int dist)
        : origin(start), destination(end), totalDistance(dist) {}

    bool isExtendedRoute() const {
        return totalDistance > 20;
    }
};

class Driver {
public:
    string driverID, driverName, licenseNumber;

    Driver() {}
    Driver(string id, string name, string license)
        : driverID(id), driverName(name), licenseNumber(license) {}
};

class Vehicle {
public:
    string vehicleCode, model;
    bool airConditioned;
    Seat seatList[MAX_SEATS];
    int totalSeats;
    Route* assignedRoute;
    Driver* assignedDriver;

    Vehicle() {}
    Vehicle(string code, string modelType, bool ac, int seats, string allowedType)
        : vehicleCode(code), model(modelType), airConditioned(ac), totalSeats(seats),
          assignedRoute(nullptr), assignedDriver(nullptr)
    {
        for (int i = 0; i < seats; i++) {
            seatList[i] = Seat(i + 1, allowedType);
        }
    }

    void setRoute(Route* route) {
        assignedRoute = route;
    }

    void setDriver(Driver* driver) {
        assignedDriver = driver;
    }

    void reserveSeat(User* user, int seatNumber) {
        if (!user->hasCompletedPayment)
            throw PaymentPendingException();

        if (seatNumber < 1 || seatNumber > totalSeats)
            throw out_of_range("Invalid seat index.");

        Seat& seat = seatList[seatNumber - 1];

        if (seat.booked)
            throw AlreadyBookedException();

        if (seat.allowedUserType != user->getUserType())
            throw UserTypeConflictException();

        seat.booked = true;
        cout << user->fullName << " has successfully reserved seat #" << seatNumber
             << " on vehicle " << vehicleCode << "." << endl;
    }
};

int main() {
    Student stu1("STD001", "Ali Khan", "ali@student.edu", true);
    Faculty fac1("FAC001", "Dr. Ahmed", "ahmed@faculty.edu", true);

    Route route1("North Nazimabad", "FAST University", 25);
    Driver driver1("DRV001", "Nadeem", "LIC-4567");

    Vehicle bus1("BUS001", "Coaster", true, 52, "Student");
    bus1.setRoute(&route1);
    bus1.setDriver(&driver1);

    try {
        bus1.reserveSeat(&stu1, 12);  
        bus1.reserveSeat(&fac1, 13);  
    } catch (exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}

