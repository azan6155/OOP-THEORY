#include <iostream>
using namespace std;

const int MAX_STOPS = 10;

class Student {
private:
    string studentID, name, email, phone, pickupStop, dropoffStop;
    bool cardActive;
public:
    Student(string id, string n, string e, string p, string pick, string drop) 
        : studentID(id), name(n), email(e), phone(p), pickupStop(pick), dropoffStop(drop), cardActive(false) {}

    void registerForTransport() {
        cardActive = true;
        cout << name << " registered for transportation.\n";
    }

    void payFees() {
        cardActive = true;
        cout << name << " paid transportation fees.\n";
    }

    void tapCard() {
        if (cardActive)
            cout << name << "'s attendance recorded.\n";
        else
            cout << "Access denied! Payment required.\n";
    }
};

class Bus {
private:
    int busID, routeNumber, capacity, currentStudents;
    string stops[MAX_STOPS];
    int stopCount;
public:
    Bus(int id, int route, int cap) : busID(id), routeNumber(route), capacity(cap), currentStudents(0), stopCount(0) {}

    void assignStudentToStop(string stop) {
        if (stopCount < MAX_STOPS) {
            stops[stopCount++] = stop;
            cout << "Stop " << stop << " added to bus " << busID << "'s route.\n";
        } else {
            cout << "Cannot add more stops to bus " << busID << "\n";
        }
    }

    void recordAttendance() {
        cout << "Recording attendance for bus " << busID << "\n";
    }
};

class Route {
private:
    int routeNumber;
    string stops[MAX_STOPS];
    int stopCount;
public:
    Route(int num) : routeNumber(num), stopCount(0) {}

    void addStop(string stop) {
        if (stopCount < MAX_STOPS) {
            stops[stopCount++] = stop;
            cout << "Stop " << stop << " added to Route " << routeNumber << "\n";
        } else {
            cout << "Cannot add more stops to Route " << routeNumber << "\n";
        }
    }
};

class Admin {
private:
    string adminID, name;
public:
    Admin(string id, string n) : adminID(id), name(n) {}

    void manageRoutes(Route &route, string stop) {
        route.addStop(stop);
    }
};

int main() {
    Student s1("123", "John Doe", "john@example.com", "1234567890", "Stop A", "Stop B");
    s1.registerForTransport();
    s1.payFees();
    s1.tapCard();

    Bus bus1(1, 101, 50);
    bus1.assignStudentToStop("Stop A");
    bus1.recordAttendance();

    Route route1(101);
    route1.addStop("Stop A");
    route1.addStop("Stop B");

    Admin admin("A001", "Admin User");
    admin.manageRoutes(route1, "Stop C");
    
    return 0;
}
