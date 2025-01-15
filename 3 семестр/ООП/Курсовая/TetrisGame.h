#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "TetrisPiece.h"
#include <ctime>

const int M = 20;
const int N = 10;

class TetrisGame {
private:
    Piece* currentPiece;
    int field[M][N] = {};
    static int totalScore;  
    int dropInterval;
    clock_t lastDropTime;

public:
    static void resetScore() { totalScore = 0; }
    static int getScore() { return totalScore; }

    TetrisGame() : currentPiece(NULL), dropInterval(700), lastDropTime(clock()) {
        memset(field, 0, sizeof(field));  
        resetScore();          
        spawnNewPiece();
    }

    ~TetrisGame() {
        delete currentPiece;
    }

    void spawnNewPiece() {
        delete currentPiece;
        int figureType = rand() % 7;
        int colorNum = 1 + rand() % 15;
        currentPiece = new TetrisPiece(figureType, colorNum);
    }

    bool check() {
        for (int i = 0; i < 4; i++) {
            int x = currentPiece->getPoints()[i].x;
            int y = currentPiece->getPoints()[i].y;
            if (x < 0 || x >= N || y < 0 || y >= M || (y >= 0 && field[y][x] != 0)) {
                return false;
            }
        }
        return true;
    }

    void clearOldPosition() {
        for (int i = 0; i < 4; i++) {
            int x = currentPiece->getPoints()[i].x;
            int y = currentPiece->getPoints()[i].y;

            if (y >= 0 && y < M) {
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x * 20 + 50, y * 20 + 50, x * 20 + 70, y * 20 + 70);
            }
        }
    }

    void hardDrop() {
        while (true) {
            clearOldPosition();
            for (int i = 0; i < 4; i++) {
                currentPiece->getPoints()[i].y++;
            }
            if (!check()) {
                for (int i = 0; i < 4; i++) {
                    currentPiece->getPoints()[i].y--;
                }
                for (int i = 0; i < 4; i++) {
                    int x = currentPiece->getPoints()[i].x;
                    int y = currentPiece->getPoints()[i].y;
                    if (y >= 0) {
                        field[y][x] = currentPiece->getColor();
                    }
                }
                clearFilledLines();
                spawnNewPiece(); 
                break;
            }
            delay(10);
        }

        totalScore += 10; 
        spawnNewPiece();
    }

    void move(int dx) {
        clearOldPosition();

        for (int i = 0; i < 4; i++) {
            currentPiece->getPoints()[i].x += dx;
        }

        if (!check()) {
            for (int i = 0; i < 4; i++) {
                currentPiece->getPoints()[i].x -= dx;
            }
        }
        update();
    }

    void rotatePiece() {
        clearOldPosition(); 
        currentPiece->rotate(N, M); 
        if (!check()) { 
            for (int i = 0; i < 3; i++) { 
                currentPiece->rotate(N, M);
            }
        }
        update(); 
    }

    void drawScore() {
        setcolor(RED);
        char scoreText[30];
        sprintf(scoreText, "Score: %d", totalScore);
        printf("%d\n", totalScore);
        outtextxy(10, 10, scoreText);
    }

    void clearFilledLines() {
        for (int i = M - 1; i >= 0; i--) {
            bool filled = true;
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0) {
                    filled = false;
                    break;
                }
            }
            if (filled) {
                totalScore += 100; 
                for (int row = i; row > 0; row--) {
                    for (int col = 0; col < N; col++) {
                        field[row][col] = field[row - 1][col];
                    }
                }
                for (int col = 0; col < N; col++) {
                    field[0][col] = 0; 
                }
                i++;
            }
        }
    }

    void update() {
        clearOldPosition();
        drawField();
        currentPiece->draw();
        drawScore(); 
    }

    void drawField() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                setcolor(WHITE);
                setfillstyle(1, field[i][j]);
                rectangle(j * 20 + 50, i * 20 + 50, j * 20 + 70, i * 20 + 70);
                floodfill(j * 20 + 51, i * 20 + 51, WHITE);
            }
        }
    }

    bool isGameOver() {
        for (int i = 0; i < N; i++) {
            if (field[0][i] != 0) return true;
        }
        return false;
    }

    void gameOver() {
        cleardevice();
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(100, 200, "GAME OVER!");
        char scoreText[30];
        sprintf(scoreText, "Final Score: %d", totalScore);
        outtextxy(100, 250, scoreText);
        delay(5000);
    }

    void dropPiece() {
        if (clock() - lastDropTime >= dropInterval) {
            clearOldPosition(); 
            for (int i = 0; i < 4; i++) {
                currentPiece->getPoints()[i].y++;
            }
            if (!check()) {
                for (int i = 0; i < 4; i++) {
                    currentPiece->getPoints()[i].y--;
                }
                for (int i = 0; i < 4; i++) {
                    int x = currentPiece->getPoints()[i].x;
                    int y = currentPiece->getPoints()[i].y;
                    if (y >= 0) {
                        field[y][x] = currentPiece->getColor();
                    }
                }
                clearFilledLines();
                spawnNewPiece(); 
            }
            update(); 
            lastDropTime = clock(); 
        }
    }
};

int TetrisGame::totalScore = 0;

#endif  
