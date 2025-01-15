#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <cmath>
#include <conio.h> 
using namespace std;

class Figure {
public:
    int x, y,xRem,yRem;
    int dx, dy;
    float angle;
public:
    Figure() : x(rand() % 500), y(rand() % 500), dx(1), dy(1),angle(0) {}
    
    Figure(int x, int y, int dx, int dy) : x(x), y(y), dx(dx), dy(dy),angle(0) {}

    ~Figure() {}

    void moveStraight(int width, int height) {
        x += dx;
        y += dy;

        if (x <= 0 || x >= width) {
            dx = -dx;
        }
        if (y <= 0 || y >= height) {
            dy = -dy;
        }
    }
    void rememberCords() {
    	this->xRem=this->x;
    	this->yRem=this->y;
	}
    void rotate() { 
        int centerX = x + dx; 
        int centerY = y + dy;
        float newX=this->xRem-(cos(this->angle)*10);
        float newY=this->yRem-sin(this->angle)*10;
        this->angle+=0.1;
        x = newX;
        y = newY;
    }

    void output() {
        cout << "Coordinates: (" << this->x << ", " << this->y << ")" << endl;
    }
};

class Line : public Figure {
public:
    int x2, y2;
    double length;

public:
    Line(int x1, int y1, int x2, int y2, int dx, int dy) 
        : Figure(x1, y1, dx, dy), x2(x2), y2(y2) {
        calculateLength();
    }

    void calculateLength() {
        length = sqrt(pow(this->x2 - this->x, 2) + pow(this->y2 - this->y, 2));
    }

    void showLength() {
        cout << "Line length: " << this->length << endl;
    }

    void output() {
        cout << "Line: (" << this->x << ", " << this->y << ") , (" << this->x2 << ", " << this->y2 << ")" << endl;
        showLength();
    }

    void draw() {
        line(x, y, x2, y2);
    }

    void moveStraight(int width, int height) {
        Figure::moveStraight(width, height);
        x2 += dx;
        y2 += dy;

        if (x2 <= 0 || x2 >= width) {
            dx = -dx;
            x2 += dx; 
        }
        if (y2 <= 0 || y2 >= height) {
            dy = -dy;
            y2 += dy; 
        }
    }
};

class Square : public Line {
	private:
		int size;
public:
    Square(int x, int y, int side, int dx, int dy) 
        : Line(x, y, x + side, y + side, dx, dy),size(this->x2-this->x) {}

    void calculatePerimeterAndArea() {
        int side = abs(this->x2 - this->x);
        cout << "Square perimeter: " << 4 * side << endl;
        cout << "Square area: " << side * side << endl;
    }

    void output() {
        Line::output();
        int side = abs(this->x2 - this->x);
        cout << "Square side: " << side << endl;
        calculatePerimeterAndArea();
    }

    void draw() {
        rectangle(x, y, x + size, y + size);
    }
};

class Circle : public Figure {
public:
    int radius;

public:
    Circle(int x, int y, int r, int dx, int dy) 
        : Figure(x, y, dx, dy), radius(r) {}

    void draw() {
        circle(x, y, radius);
    }
};

class MyRectangle : public Figure {
private:
    int width, height;

public:
    MyRectangle(int x, int y, int w, int h, int dx, int dy) 
        : Figure(x, y, dx, dy), width(w), height(h) {}

    void draw() {
        ::rectangle(x, y, x + width, y + height);
    }

    void calculatePerimeterAndArea() {
        cout << "Rectangle perimeter: " << 2 * (width + height) << endl;
        cout << "Rectangle area: " << width * height << endl;
    }
    void output() {
        cout << "Rectangle: (" << this->x << ", " << this->y << "), width: " 
             << width << ", height: " << height << endl;
        calculatePerimeterAndArea();
    }
};

class MyEllipse : public Circle {
private:
    int radius2;
    
public:
    MyEllipse(int x, int y, int r1, int r2, int dx, int dy) 
        : Circle(x, y, r1, dx, dy), radius2(r2) {}

    void draw() {
        ellipse(x, y, 0, 360, radius, radius2);
    }

    void input() {
        cout << "Enter x, y and radius, radius2: ";
        cin >> this->x >> this->y >> this->radius >> this->radius2;
    }

    void output() const {
        cout << "Ellipse center: (" << this->x << ", " << this->y << "), radius: " 
             << this->radius << ", " << this->radius2 << endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    initwindow(800, 600);

    cout << "Random line:" << endl;
    Line line1(rand() % 400, rand() % 400, rand() % 400 + 100, rand() % 400 + 100, 1, 1);
    line1.output();
    
    cout << endl << "Custom constructor line:" << endl;
    Line line2(10, 10, 20, 20, 1, 1);
    line2.output();
    cout << endl;

    cout << "Random square:" << endl;
    Square square1(rand() % 400, rand() % 400, rand() % 50 + 10, 1, 1);
    square1.output();
    cout << endl;

    cout << "Custom constructor square:" << endl;
    Square square2(30, 30, 10, 1, 1);
    square2.output();
    cout << endl;

    cout << "Random rectangle:" << endl;
    MyRectangle rect1(rand() % 400, rand() % 400, rand() % 50 + 10, rand() % 50 + 10, 1, 1);
    rect1.output();
    cout << endl;

    cout << "Custom constructor rectangle:" << endl;
    MyRectangle rect2(50, 50, 12, 20, 1, 1);
    rect2.output();
    cout << endl;

    cout << "Random circle:" << endl;
    Circle circle1(rand() % 400, rand() % 400, rand() % 50 + 10, 1, 1);
    circle1.output();
    cout << endl;

    cout << "Custom constructor circle:" << endl;
    Circle circle2(70, 70, 15, 1, 1);
    circle2.output();
    cout << endl;

    cout << "Random ellipse:" << endl;
    MyEllipse ellipse1(rand() % 400, rand() % 400, rand() % 50 + 10, rand() % 50 + 10, 1, 1);
    ellipse1.output();
    cout << endl;

    cout << "Custom constructor ellipse:" << endl;
    MyEllipse ellipse2(90, 90, 15, 10, 1, 1);
    ellipse2.output();
    cout << endl;

    cout << "Dynamic array with rectangle's custom constructor:" << endl;
    MyRectangle* rectArray = new MyRectangle[3] {
        MyRectangle(0, 0, 20, 30, 1, 1),
        MyRectangle(10, 10, 40, 50, 1, 1),
        MyRectangle(20, 20, 60, 70, 1, 1)
    };

    for (int i = 0; i < 3; ++i) {
        rectArray[i].output();
    }
	int mode=0;
    while (true) {
        cleardevice();
        line1.draw();
        square1.draw();
        circle1.draw();
        ellipse1.draw();
        rect1.draw();
		switch(mode) {
			case 0:
            	line1.moveStraight(800, 600);
                square1.moveStraight(800, 600);
                circle1.moveStraight(800, 600);
                ellipse1.moveStraight(800, 600);
                rect1.moveStraight(800, 600);
                break;
            case 1:
                    line1.rotate();
                    square1.rotate();
                    circle1.rotate();
                    ellipse1.rotate();
                    rect1.rotate();
                    break;
            	
		}
        if (kbhit()) {
            char ch = getch(); 
            switch (ch) {
                case 'S': 
                    mode=0;
                    break;
                case 'R': 
                    line1.rememberCords();
                    square1.rememberCords();
                    circle1.rememberCords();
                    ellipse1.rememberCords();
                    rect1.rememberCords();
                    mode=1;
                	break;
            }
        }

        delay(20);
    }
    closegraph();
    delete[] rectArray;
    return 0;
}
