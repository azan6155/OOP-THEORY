#include <iostream>
using namespace std;

const int MaxStops = 10;

class User
{
protected:
    string userID, fullName, emailAddress, contactNumber;
    bool isCardActive;

public:
    User(string id, string name, string email, string phone)
        : userID(id), fullName(name), emailAddress(email), contactNumber(phone), isCardActive(false) {}

    virtual void payTransportFees() = 0;

    void enrollInTransport()
    {
        isCardActive = true;
        cout << fullName << " has enrolled in transport services" << endl;
    }

    void scanCard()
    {
        if (isCardActive)
        {
            cout << fullName << "'s attendance marked successfully" << endl;
        }
        else
        {
            cout << "Access denied! Please pay the transport fee first." << endl;
        }
    }
};

class Student : public User
{
    string pickupLocation, dropoffLocation;

public:
    Student(string id, string name, string email, string phone, string pickup, string drop)
        : User(id, name, email, phone), pickupLocation(pickup), dropoffLocation(drop) {}

    void payTransportFees() override
    {
        isCardActive = true;
        cout << fullName << " has paid the transport fees for this semester" << endl;
    }
};

class Teacher : public User
{
public:
    Teacher(string id, string name, string email, string phone)
        : User(id, name, email, phone) {}

    void payTransportFees() override
    {
        isCardActive = true;
        cout << fullName << " has paid the monthly transport fee" << endl;
    }
};

class Bus
{
    int busID, routeID, maxCapacity, studentCount;
    string stopList[MaxStops];
    int totalStops;

public:
    Bus(int id, int route, int capacity)
        : busID(id), routeID(route), maxCapacity(capacity), studentCount(0), totalStops(0) {}

    void addStop(string stop)
    {
        if (totalStops < MaxStops)
        {
            stopList[totalStops++] = stop;
            cout << "Stop added to Bus #" << busID << endl;
        }
        else
        {
            cout << "No more stops can be added to this bus" << endl;
        }
    }

    void takeAttendance()
    {
        cout << "Taking attendance for Bus #" << busID << endl;
    }
};

class Route
{
    int routeID;
    string stopNames[MaxStops];
    int currentStopCount;

public:
    Route(int id) : routeID(id), currentStopCount(0) {}

    void insertStop(string stop)
    {
        if (currentStopCount < MaxStops)
        {
            stopNames[currentStopCount++] = stop;
            cout << "Stop added to Route #" << routeID << endl;
        }
        else
        {
            cout << "Maximum number of stops reached for this route" << endl;
        }
    }

    bool operator==(const Route &other) const
    {
        if (routeID != other.routeID || currentStopCount != other.currentStopCount)
        {
            return false;
        }

        for (int i = 0; i < currentStopCount; i++)
        {
            if (stopNames[i] != other.stopNames[i])
                return false;
        }
        return true;
    }
};

class Admin
{
    string adminID, adminName;

public:
    Admin(string id, string name) : adminID(id), adminName(name) {}

    void updateRoute(Route &route, string newStop)
    {
        route.insertStop(newStop);
    }
};

int main()
{
    Student s1("S1001", "Ali Raza", "ali.raza@uni.pk", "03001234567", "North Nazimabad", "Gulshan-e-Iqbal");
    Teacher t1("T2001", "Dr. Ahmed", "dr.ahmed@uni.pk", "03211234567");

    s1.enrollInTransport();
    s1.payTransportFees();
    s1.scanCard();

    t1.enrollInTransport();
    t1.payTransportFees();
    t1.scanCard();

    Bus bus1(10, 202, 40);
    bus1.addStop("North Nazimabad");
    bus1.takeAttendance();

    Route r1(202), r2(203);
    r1.insertStop("North Nazimabad");
    r1.insertStop("Gulshan-e-Iqbal");

    r2.insertStop("North Nazimabad");
    r2.insertStop("Gulshan-e-Iqbal");

    if (r1 == r2)
    {
        cout << "Both routes are identical" << endl;
    }
    else
    {
        cout << "Routes are not the same" << endl;
    }

    Admin admin1("ADM01", "Ms. Fatima");
    admin1.updateRoute(r1, "Bahadurabad");

    return 0;
}

