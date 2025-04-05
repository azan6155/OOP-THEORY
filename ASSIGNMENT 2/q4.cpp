#include <iostream>
using namespace std;

typedef unsigned long ulong;

ulong generateHash(const string& pwd) {
    ulong hash = 5381;
    for (char ch : pwd) hash = hash * 33 + ch;
    return hash;
}

class User {
protected:
    string name, email;
    int id, permCount;
    ulong hashPwd;
    string perms[5];

public:
    User(string n, int uid, string mail, string pwd, string p[], int pc)
        : name(n), id(uid), email(mail), permCount(pc), hashPwd(generateHash(pwd)) {
        for (int i = 0; i < pc; i++) perms[i] = p[i];
    }

    virtual void display() {
        cout << "User: " << name << " (ID: " << id << ")\nEmail: " << email << "\nPerms: ";
        for (int i = 0; i < permCount; i++) cout << perms[i] << " ";
        cout << endl;
    }

    bool authenticate(const string& pwd) {
        return hashPwd == generateHash(pwd);
    }

    bool hasPermission(const string& perm) {
        for (int i = 0; i < permCount; i++) if (perms[i] == perm) return true;
        return false;
    }

    virtual bool accessLab() { return hasPermission("fullLabAccess"); }

    int getID() const { return id; }
};

class Student : public User {
protected:
    int assignments[5]{};

public:
    Student(string n, int uid, string mail, string pwd)
        : User(n, uid, mail, pwd, new string[1]{"submitAssignment"}, 1) {}

    void display() override {
        cout << "[Student] ";
        User::display();
    }

    void submit(int idx) {
        if (idx >= 0 && idx < 5) {
            assignments[idx] = 1;
            cout << "Submitted assignment " << idx + 1 << endl;
        }
    }
};

class TA : public Student {
    Student* assigned[10]{};
    string projects[2];
    int count = 0, projCount = 0;

public:
    TA(string n, int uid, string mail, string pwd)
        : Student(n, uid, mail, pwd) {
        string extraPerms[] = {"viewProjects", "manageStudents", "submitAssignment"};
        for (int i = 0; i < 3; i++) perms[i] = extraPerms[i];
        permCount = 3;
    }

    void display() override {
        cout << "[TA] ";
        User::display();
    }

    bool assign(Student* s) {
        if (count < 10) { assigned[count++] = s; return true; }
        return false;
    }

    bool startProject(string proj) {
        if (projCount < 2) { projects[projCount++] = proj; return true; }
        return false;
    }
};

class Professor : public User {
public:
    Professor(string n, int uid, string mail, string pwd)
        : User(n, uid, mail, pwd, new string[2]{"assignProjects", "fullLabAccess"}, 2) {}

    void display() override {
        cout << "[Professor] ";
        User::display();
    }

    void assignToTA(TA& ta, string project) {
        if (ta.startProject(project))
            cout << "Assigned '" << project << "' to TA " << ta.getID() << endl;
        else
            cout << "TA cannot take more projects.\n";
    }
};

void perform(User* user, string action, string pwd) {
    if (!user->authenticate(pwd)) cout << "Auth failed.\n";
    else if (user->hasPermission(action)) cout << "Action '" << action << "' successful.\n";
    else cout << "Permission denied.\n";
}

int main() {
    Student s1("Azan", 101, "azoo.edu", "pass123");
    TA ta1("Ali", 102, "a@uni.edu", "ta321");
    Professor p1("Zahid", 103, "z@uni.edu", "prof007");

    s1.display();
    ta1.display();
    p1.display();

    perform(&s1, "submitAssignment", "pass123");
    perform(&ta1, "manageStudents", "ta321");
    perform(&p1, "assignProjects", "prof007");

    p1.assignToTA(ta1, "AI Research");
    p1.assignToTA(ta1, "Cloud Security");
    p1.assignToTA(ta1, "Quantum Comp");

    return 0;
}

