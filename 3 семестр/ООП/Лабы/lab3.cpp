#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

const int POINT_COUNT = 100;
using namespace std;

class tPoint {
private:
    int x; 
    int y; 
    int dx; 
    int dy; 
public:

    tPoint() : x(0), y(0), dx(1), dy(1) {}

    tPoint(int x, int y) : x(x), y(y) {
        if (rand() % 2 == 0) {
            dx = 1;
        } else {
            dx = -1;
        }

        if (rand() % 2 == 0) {
            dy = 1;
        } else {
            dy = -1;
        }
    }

    void getCoordinates(int &cordX, int &cordY) {
        cordX = x;
        cordY = y;
    }

    void draw() {
        setcolor(WHITE); 
        setfillstyle(SOLID_FILL, WHITE); 
        fillellipse(x, y, 2, 2); 
    }

    void moveStraight(int width, int height) {
        x += dx;
        y += dy;

        if (x <= 0 || x >= width) {
            dx = -dx;
            x += dx; 
        }
        if (y <= 0 || y >= height) {
            dy = -dy;
            y += dy; 
        }
    }

    void moveRandomly(int width, int height) {
        dx = (rand() % 5) - 2; 
        dy = (rand() % 5) - 2; 

        x += dx; 
        y += dy; 

        if (x < 0) {
            x = 0; 
        } else if (x >= width) {
            x = width - 1; 
        }

        if (y < 0) {
            y = 0; 
        } else if (y >= height) {
            y = height - 1;
        }
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    tPoint* points = new tPoint[POINT_COUNT];

    for (int i = 0; i < POINT_COUNT; i++) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        points[i] = tPoint(x, y);
    }

    bool useStraightMovement = true;

    while (true) {
        if (kbhit()) {
            char key = getch();
            if (key == 'S' || key == 's') {
                useStraightMovement = true;
            } else if (key == 'R' || key == 'r') {
                useStraightMovement = false;
            } else if (key == 27) { 
                break;
            }
        }

        cleardevice(); 
        for (int i = 0; i < POINT_COUNT; ++i) {
            points[i].draw(); 
            if (useStraightMovement) {
                points[i].moveStraight(getmaxx(), getmaxy()); 
            } else {
                points[i].moveRandomly(getmaxx(), getmaxy());
            }
        }
        delay(10); 
    }

    delete[] points;
    closegraph();
    return 0;
}
