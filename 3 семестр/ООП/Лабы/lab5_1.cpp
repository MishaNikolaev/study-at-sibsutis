#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const double pi = 3.14159265;

class Figure
{
    protected:
    int x, y;
    public:
    Figure()
    {
        x = rand() % 100;
        y = rand() % 100;
    }

    Figure(int x_, int y_) : x(x_), y(y_) {}

    virtual void Input() {};
    virtual void Output() const {};

    virtual ~Figure() {}

};


class Line : public Figure
{
    protected:
    int x2, y2;

    public:
    Line() : Figure(), x2(rand() % 100), y2(rand() % 100) {}

    Line(int x_, int y_, int x2_, int y2_) : Figure(x_, y_), x2(x2_), y2(y2_) {}

    void Input() override
    {
        cout << "Enter x and y for start point (x, y): ";
        cin >> x >> y;
        cout << "Enter x and y for last point (x2, y2): ";
        cin >> x2 >> y2;
    }

    void Output() const override
    {
        cout << "Your Line: ("<< x << ", " << y << ") - (" << x2 << ", " << y2 << ")\n";
        cout << "Lenth of Line: " << Length() << endl  << endl;
    }

    private:
    float Length() const
    {
        return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }

};

class Rectangle : public Figure
{
    protected:
    int width, height;

    public:
    Rectangle() : Figure(), width(rand() % 50), height(rand() % 50) {}

    Rectangle(int x_, int y_, int width_, int height_) : Figure(x_, y_), width(width_), height(height_) {}

    int Perimeter() const
    {
        return 2 * (width + height);
    }

    int Area() const
    {
        return width * height;
    }

    void Input() override
    {
        cout << "Enter x and y for Rectangle start point (x, y): ";
        cin >> x >> y;
        cout << "Enter width and height for sides: ";
        cin >> width >> height;
    }

    void Output() const override
    {
        cout << "Your Rectangle start point: ("<< x << ", " << y << ")\n";
        cout << "Rectangle size: (" << width << "x" << height << ")\n";
        cout << "Perimeter: " << Perimeter() << endl;
        cout << "Area: " << Area() << endl << endl;
    }

};


class Square : public Rectangle
{
    public:
    Square() : Rectangle()
    {
        width = height = rand() % 50;
    }
    Square(int x_, int y_, int side_) : Rectangle(x_, y_, side_, side_) {}

    void Input() override
    {
        cout << "Enter x and y for Square start point (x, y): ";
        cin >> x >> y;
        cout << "Enter side: ";
        cin >> width;
        height = width;
    }

    void Output() const override
    {
        cout << "Your Square start point: ("<< x << ", " << y << ")\n";
        cout << "Square size: (" << width << "x" << height << ")\n";
        cout << "Perimeter: " << Perimeter() << endl;
        cout << "Area: " << Area() << endl << endl;
    }
};


class Circle : public Line
{
    public:
    Circle() : Line() {}

    Circle (int x1_, int y1_, int x2_, int y2_) : Line(x1_, y1_, x2_, y2_) {}

    float Raduis() const
    {
        return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }

    double Area() const
    {
        return pi * (2 * pow(Raduis(), 2));
    }

    double LenthOfCircle() const
    {
        return pi * (2 * Raduis());
    }

    void Input() override
    {
        cout << "Enter x and y for radius start point (x, y): ";
        cin >> x >> y;
        cout << "Enter x and y for radius last point (x2, y2): ";
        cin >> x2 >> y2;
    }

    void Output() const override
    {
        cout << "Your Circle radius: ("<< x << ", " << y << ") - (" << x2 << ", " << y2 << ")\n";
        cout << "Lenth of Radius: " << Raduis() << endl;
        cout << "Lenth of Circle " << LenthOfCircle() << endl;
        cout << "Area: " << Area() << endl << endl;
    }

};

class Ellipse : public Figure {
    protected:
    double majorAxis;
    double minorAxis;

    public:
    Ellipse() : Figure()
    {
        majorAxis = rand() % 50 + 1;
        minorAxis = rand() % 50 + 1;
    }


    Ellipse(double x_, double y_, double major, double minor) : Figure(x_, y_), majorAxis(major), minorAxis(minor) {}

    double Area() const
    {
        return pi * majorAxis * minorAxis;
    }

    double Perimeter() const
    {
        return pi * (3 * (majorAxis + minorAxis) - sqrt((3 * majorAxis + minorAxis) * (majorAxis + 3 * minorAxis)));
    }

    void Input() override
    {
        cout << "Enter x and y for Ellipse start point (x, y): ";
        cin >> x >> y;
        cout << "Enter lenth of major Axis: ";
        cin >> majorAxis;
        cout << "Enter lenth of minor Axis: ";
        cin >> minorAxis;
    }

    void Output() const override
    {
        cout << "Ellipce center: (" << x << ", " << y << ")\n";
        cout << "Major Axis: " << majorAxis << "\n";
        cout << "Minor Axis: " << minorAxis << "\n";
        cout << "Area: " << Area() << "\n";
        cout << "Perimeter: " << Perimeter() << endl << endl;
    }

};

int main(int argc, char const *argv[])
{
    srand(time(nullptr));

    Line line;
    line.Output();

    Square square;
    square.Output();

    Rectangle rectangle;
    rectangle.Output();

    Circle circle;
    circle.Output();

    Ellipse ellipse;
    ellipse.Output();



    Rectangle* rectangles = new Rectangle[3]
    {
        Rectangle(0, 0, 10, 5),
        Rectangle(2, 2, 20, 10),
        Rectangle(5, 5, 15, 7)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "Rectangle " << i + 1 << ":" << endl;
        rectangles[i].Output();
        cout << endl;
    }

    delete[] rectangles;


}
