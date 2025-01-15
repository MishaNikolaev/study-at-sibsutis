#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Figure {
public:
    int x, y;

    Figure() : x(rand() % 500), y(rand() % 500) {}
    Figure(int x, int y) : x(x), y(y) {}
   ~Figure() {}

    virtual void output() = 0; 
    virtual double calculatePerimeter() = 0; 
};

class Line : public Figure {
public:
    int x2, y2;
    double length;
    static int count;
    static int exists;

    Line(int x1, int y1, int x2, int y2) : Figure(x1, y1), x2(x2), y2(y2) {
        calculateLength();
        count++;
        exists++;
    }

    ~Line() {
        exists--;
    }

    void calculateLength() {
        length = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }

    void output() override {
        cout << "Line: (" << x << ", " << y << ") to (" << x2 << ", " << y2 << ") with length " << length << endl;
    }

    double calculatePerimeter() override {
        return length; 
    }

    static void displayCounts() {
        cout << "Created Lines: " << count << ", Existing Lines: " << exists << endl;
    }
};

int Line::count = 0;
int Line::exists = 0;

class Square : public Line {
public:
    static int count;   
    static int exists;  
    Square(int x, int y, int side) : Line(x, y, x + side, y + side) {
        count++;
        exists++;
    }

    ~Square() {
        exists--;
    }

    void output() override {
        cout << "Square: (" << x << ", " << y << "), side: " << (x2 - x) << endl;
    }

    double calculatePerimeter() override {
        return 4 * (x2 - x); 
    }

    static void displayCounts() {
        cout << "Created Squares: " << count << ", Existing Squares: " << exists << endl;
    }
};

int Square::count = 0;
int Square::exists = 0;

class MyRectangle : public Square {
private:
    static int count;
    static int exists;
    int width, height;

public:
    MyRectangle(int x, int y, int w, int h) : Square(x, y, w), width(w), height(h) {
        count++;
        exists++;
    }

    ~MyRectangle() {
        exists--;
    }

    void output() override {
        cout << "Rectangle: (" << x << ", " << y << "), width: " << width << ", height: " << height << endl;
    }

    double calculatePerimeter() override {
        return 2 * (width + height); 
    }

    static void displayCounts() {
        cout << "Created Rectangles: " << count << ", Existing Rectangles: " << exists << endl;
    }
};

int MyRectangle::count = 0;
int MyRectangle::exists = 0;

class Circle : public Figure {
protected: 
    int radius;
    static int count;
    static int exists;

public:
    Circle(int x, int y, int r) : Figure(x, y), radius(r) {
        count++;
        exists++;
    }

    ~Circle() {
        exists--;
    }

    void output() override {
        cout << "Circle: (" << x << ", " << y << "), radius: " << radius << endl;
    }

    double calculatePerimeter() override {
        return 2 * M_PI * radius; 
    }

    static void displayCounts() {
        cout << "Created Circles: " << count << ", Existing Circles: " << exists << endl;
    }
};

int Circle::count = 0;
int Circle::exists = 0;

class MyEllipse : public Circle {
private:
    int radius2;

public:
    MyEllipse(int x, int y, int r1, int r2) : Circle(x, y, r1), radius2(r2) {
        count++;
        exists++;
    }

    ~MyEllipse() {
        exists--;
    }

    void output() override {
        cout << "Ellipse center: (" << x << ", " << y << "), radius1: " << radius << ", radius2: " << radius2 << endl;
    }

    double calculatePerimeter() override {
        return M_PI * (3 * (radius + radius2) - sqrt((3 * radius) + radius2) * sqrt(radius + 3 * radius2));
    }

    static void displayCounts() {
        cout << "Created Ellipses: " << count << ", Existing Ellipses: " << exists << endl;
    }
};


int main() {
    srand(static_cast<unsigned int>(time(0))); 
    
    cout << "Line" << endl;
    Line line1(0, 0, 3, 4);
    line1.output();
	cout << endl;
	
	cout << "Square" << endl;
    Square square1(1, 1, 5);
    square1.output();
	cout << endl;
	
	cout << "Rectangle" << endl;
    MyRectangle myRect1(2, 2, 4, 6);
    myRect1.output();
	cout << endl;

	cout << "Circle" << endl;
    Circle circle1(5, 5, 3);
    circle1.output();
    cout << endl;

	cout << "Ellipse" << endl;
    MyEllipse ellipse1(6, 6, 3, 5);
    ellipse1.output();
    cout << endl;
    
    cout << "Count and exist in rectangle" << endl;
    MyRectangle::displayCounts();
	cout << endl;
	
    MyRectangle* rectPtr = NULL;
    cout << "Create object na ykazatel" << endl;
    rectPtr = new MyRectangle(2, 3, 7, 5);
    rectPtr->output();
    MyRectangle::displayCounts();
    cout << endl;
	cout << "Dynamic object rectangle" << endl;
    MyRectangle* dynamicRect = new MyRectangle(3, 3, 10, 5);
    dynamicRect->output();
    MyRectangle::displayCounts();
    cout << endl;
    Figure** figures = new Figure*[4];
    figures[0] = new Square(0, 0, 5);
    figures[1] = new MyRectangle(1, 1, 4, 6);
    figures[2] = new Circle(2, 2, 3);
    figures[3] = new MyEllipse(3, 3, 2, 5);

	cout << "Count objects rectangle" << endl;
    MyRectangle::displayCounts();
	
	cout << endl;
    cout << "Figure perimetrs in array." << endl;
    for (int i = 0; i < 4; ++i) {
        figures[i]->output();
        cout << "Perimeter: " << figures[i]->calculatePerimeter() << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete figures[i];
    }
    delete[] figures;

    MyRectangle::displayCounts();

    delete rectPtr;
    delete dynamicRect;
    return 0;
}
