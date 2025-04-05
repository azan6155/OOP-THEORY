#include <iostream>
#include <string>
using namespace std;

class DeliveryVehicle {
protected:
    string id;
    static int activeDeliveries;

public:
    DeliveryVehicle(string vid) : id(vid) { activeDeliveries++; }
    virtual ~DeliveryVehicle() { activeDeliveries--; }

    virtual void planRoute() = 0;
    virtual void estimateTime() = 0;
    virtual void move() { cout << "Vehicle moving...\n"; }

    static int getActiveCount() { return activeDeliveries; }
    string getID() const { return id; }

    friend bool operator==(const DeliveryVehicle& a, const DeliveryVehicle& b) {
        return a.id == b.id;
    }
};

int DeliveryVehicle::activeDeliveries = 0;

class AerialCourier : public DeliveryVehicle {
public:
    AerialCourier(string vid) : DeliveryVehicle(vid) {}
    void planRoute() override { cout << "AerialCourier: Mapping air route...\n"; }
    void estimateTime() override { cout << "Estimated time: 12 minutes.\n"; }
    void move() override { cout << "Flying to destination...\n"; }
};

class TimeGlider : public DeliveryVehicle {
public:
    TimeGlider(string vid) : DeliveryVehicle(vid) {}
    void planRoute() override { cout << "TimeGlider: Checking timeline path...\n"; }
    void estimateTime() override { cout << "Instant delivery via time jump.\n"; }
    void move() override { cout << "Gliding through time...\n"; }
};

class HyperTunnel : public DeliveryVehicle {
public:
    HyperTunnel(string vid) : DeliveryVehicle(vid) {}
    void planRoute() override { cout << "HyperTunnel: Navigating sub-layer tunnel system...\n"; }
    void estimateTime() override { cout << "Estimated time: 18 minutes.\n"; }
    void move() override { cout << "Zipping through hyper tubes...\n"; }
};

// Command function overloading
void processCommand(string action, int pkgID) {
    cout << "Command: " << action << " | Package #" << pkgID << endl;
}

void processCommand(string action, int pkgID, string priority) {
    cout << "Command: " << action << " | Package #" << pkgID << " | Priority: " << priority << endl;
}

int main() {
    AerialCourier drone("D1001");
    TimeGlider glider("TG2002");
    HyperTunnel tunnel("HT3003");

    drone.planRoute();
    drone.estimateTime();
    drone.move();

    glider.planRoute();
    glider.estimateTime();
    glider.move();

    tunnel.planRoute();
    tunnel.estimateTime();
    tunnel.move();

    processCommand("Dispatch", 501);
    processCommand("Dispatch", 502, "High");

    if (drone == glider)
        cout << "Drone and Glider have matching IDs.\n";
    else
        cout << "Drone and Glider are different units.\n";

    cout << "Currently active deliveries: " << DeliveryVehicle::getActiveCount() << endl;
    return 0;
}

