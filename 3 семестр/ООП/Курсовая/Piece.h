#ifndef PIECE_H
#define PIECE_H

#include <graphics.h>
#include <iostream>
#include <cstring> 

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class Piece {
protected:
    Point a[4]; 
    int color; 

public:
    Piece() : color(0) {
        memset(a, 0, sizeof(a)); 
    }

    Piece(int colorValue) : color(colorValue) {
        memset(a, 0, sizeof(a)); 
    }

    virtual void draw() = 0; 
    virtual void rotate(int N, int M) = 0;
    Point* getPoints() { return a; }
    int getColor() { return color; }
    virtual ~Piece() {}

    static const int figures[7][4][2];
};

const int Piece::figures[7][4][2] = {
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},  
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}},  
    {{0, 1}, {0, 0}, {1, 0}, {1, -1}}, 
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}},  
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},  
    {{1, 0}, {0, 0}, {0, 1}, {1, 1}},  
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}   
};

#endif 
