#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "TetrisGame.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\MinGW\\lib\\libbgi.a");
    srand(time(NULL));  
    TetrisGame game;

    while (true) {
        delay(100);
        if (GetAsyncKeyState(VK_ESCAPE)) break;
        if (game.isGameOver()) {
            game.gameOver();
            break;
        }

        if (GetAsyncKeyState(VK_LEFT)) game.move(-1);
        if (GetAsyncKeyState(VK_RIGHT)) game.move(1);
        if (GetAsyncKeyState(VK_UP)) game.rotatePiece();
        if (GetAsyncKeyState(VK_DOWN)) game.hardDrop();

        game.dropPiece();
        game.update();
    }

    closegraph();
    return 0;
}
