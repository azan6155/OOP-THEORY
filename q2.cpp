#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Ball {
public:
    int x, y;

    Ball() : x(0), y(0) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void getPosition() const {
        cout << "Ball Position: (" << x << "," << y << ")" << endl;
    }
};

class Robot {
public:
    string name;
    int hits;

    Robot(string n) : name(n), hits(0) {}

    void hitBall(Ball &b, const string &direction) {
        hits++;
        if (direction == "up") b.move(0, 1);
        else if (direction == "down") b.move(0, -1);
        else if (direction == "left") b.move(-1, 0);
        else if (direction == "right") b.move(1, 0);
        cout << name << " hit the ball " << direction << ". Hits: " << hits << endl;
    }
};

class Game {
public:
    Ball b;
    Robot *team1, *team2;

    Game(Robot *r1, Robot *r2) : team1(r1), team2(r2) {}

    void play(Robot *r) {
        cout << r->name << " is playing!" << endl;
        while (b.x != 5 || b.y != 5) {  // Goal is at (5, 5)
            string directions[] = {"up", "down", "left", "right"};
            r->hitBall(b, directions[rand() % 4]);
            b.getPosition();
        }
    }

    void startGame() {
        srand(time(0));
        play(team1);
        b = Ball(); // Reset ball for second team
        play(team2);
        declareWinner();
    }

    void declareWinner() {
        cout << (team1->hits < team2->hits ? team1->name : team2->name) << " wins!" << endl;
    }
};

int main() {
    Robot r1("Orca"), r2("Livyatan");
    Game g(&r1, &r2);
    g.startGame();

    return 0;
}

