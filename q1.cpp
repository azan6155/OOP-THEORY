#include <iostream>
#include <string>

using namespace std;

class Skill {
public:
    int id;
    string name;

    Skill(int id, string name) : id(id), name(name) {}
};

class Sport {
public:
    int id;
    string name;
    Skill* skill;

    Sport(int id, string name, Skill* skill) : id(id), name(name), skill(skill) {}

    void ShowSportInfo() {
        cout << "Sport: " << name << "\nRequired Skill: " << skill->name << endl;
    }
};

class Mentor {
public:
    int id;
    string name;
    Sport* sport;

    Mentor(int id, string name, Sport* sport) : id(id), name(name), sport(sport) {}

    void AssignMentor() {
        cout << name << " is mentoring in " << sport->name << endl;
    }
};

class Student {
public:
    int id;
    string name;
    Sport* sport;

    Student(int id, string name, Sport* sport) : id(id), name(name), sport(sport) {}

    void RegisterMentor(Mentor* mentor) {
        mentor->AssignMentor();
        cout << name << " is registered with " << mentor->name << endl;
    }
};

int main() {
    Skill skill(1, "Backhand");
    Sport tennis(1, "Tennis", &skill);
    Mentor mentor(1, "Coach Ali", &tennis);
    Student student(1, "Saad", &tennis);

    student.RegisterMentor(&mentor);
    tennis.ShowSportInfo();

    return 0;
}

