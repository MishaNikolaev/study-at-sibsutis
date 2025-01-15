#ifndef SHAPE_H
#define SHAPE_H

#include "Piece.h"

class Shape : public Piece {
protected:
    void initializePoints(const int figures[7][4][2], int figureType) {
        for (int i = 0; i < 4; i++) {
            a[i] = Point(figures[figureType][i][0], figures[figureType][i][1]);
        }
    }
public:
    Shape(int c) : Piece(c) {}  
};

#endif
