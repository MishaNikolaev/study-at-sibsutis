#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include "Shape.h"
#include <cstdlib>

class TetrisPiece : public Shape {
public:
    TetrisPiece(int figureType, int c) : Shape(c) {
        initializePoints(Piece::figures, figureType); 
    }

    void draw() override {
        for (int i = 0; i < 4; i++) {
            int x = a[i].x * 20 + 50; 
            int y = a[i].y * 20 + 50;
            setfillstyle(1, color); 
            floodfill(x + 1, y + 1, WHITE); 
        }
    }

    void rotate(int N, int M) override {
        Point center = a[1];
        Point temp[4];
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - center.y;
            int y = a[i].x - center.x;
            temp[i] = Point(center.x - x, center.y + y);
        }

        Point old[4];
        for (int i = 0; i < 4; i++) {
            old[i] = a[i];
        }

        for (int i = 0; i < 4; i++) {
            a[i] = temp[i];
        }

        if (!check(N, M)) {
            for (int i = 0; i < 4; i++) {
                a[i] = old[i];
            }
        }
    }

    bool check(int N, int M) {
        for (int i = 0; i < 4; i++) {
            int x = a[i].x;
            int y = a[i].y;
            if (x < 0 || x >= N || y < 0 || y >= M) {
                return false;
            }
        }
        return true;
    }
};

#endif 

