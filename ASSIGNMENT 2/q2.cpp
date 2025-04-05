#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ghost {
protected:
    string name;
    int scareLevel;
public:
    Ghost(string n) : name(n), scareLevel(rand() % 10 + 1) {}
    virtual void haunt() const = 0;
    int getScareLevel() const { return scareLevel; }
    virtual ~Ghost() {}
};

class Wraith : public Ghost {
public:
    Wraith(string n) : Ghost(n) {}
    void haunt() const override { cout << name << " (Wraith) rattles chains!\n"; }
};

class Screecher : public Ghost {
public:
    Screecher(string n) : Ghost(n) {}
    void haunt() const override { cout << name << " (Screecher) shrieks loudly!\n"; }
};

class Visitor {
    string name;
    int bravery;
public:
    Visitor(string n, int b) : name(n), bravery(b) {}
    void react(int scare) const {
        if (scare < bravery) cout << name << " laughs at the ghost!\n";
        else if (scare > bravery) cout << name << " runs away in fear!\n";
        else cout << name << " stands frozen in place!\n";
    }
};

class HauntedHouse {
    string title;
    Ghost* ghosts[2];
    int count;
public:
    HauntedHouse(string t) : title(t), count(0) {}
    void add(Ghost* g) { if (count < 2) ghosts[count++] = g; }
    void enter(Visitor v) const {
        cout << "\n" << v.name << " enters " << title << "...\n";
        for (int i = 0; i < count; i++) {
            ghosts[i]->haunt();
            v.react(ghosts[i]->getScareLevel());
        }
    }
    ~HauntedHouse() { for (int i = 0; i < count; i++) delete ghosts[i]; }
};

int main() {
    srand(time(0));
    
    HauntedHouse house1("The Foggy Manor");
    house1.add(new Wraith("Saad"));
    house1.add(new Screecher("Tariq"));

    Visitor visitors[] = {
        Visitor("Hassan", 3),
        Visitor("Usman", 6),
        Visitor("Kamran", 9)
    };

    for (auto& v : visitors) house1.enter(v);

    return 0;
}

