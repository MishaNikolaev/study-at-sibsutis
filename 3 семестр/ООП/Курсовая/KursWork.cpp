#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
const int M = 20;
const int N = 10;

int figures[7][4][2] = {
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
    {{0, 1}, {0, 0}, {1, 0}, {1, -1}},
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    {{1, 0}, {0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}
};

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
    virtual void draw() = 0;
    virtual void rotate() = 0;
    Point* getPoints() { return a; }
    int getColor() { return color; }
    virtual ~Piece() {}
};

class TetrisPiece : public Piece {
public:
    TetrisPiece(int figureType, int c) {
        color = c;
        for (int i = 0; i < 4; i++) {
            a[i] = Point(figures[figureType][i][0], figures[figureType][i][1]);
        }
    }

    void draw() override {
        for (int i = 0; i < 4; i++) {
            int x = a[i].x * 20 + 50;
            int y = a[i].y * 20 + 50;
            setfillstyle(1, color);
            floodfill(x+1,y+1,WHITE);
        }
    }

    void rotate() override {
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

        if (!check()) {
            for (int i = 0; i < 4; i++) {
                a[i] = old[i];
            }
        }
    }

    bool check() {
        for (int i = 0; i < 4; i++) {
            int x = a[i].x;
            int y = a[i].y;
            if (x < 0 || x >= N || y >= M) {
                return false;
            }
        }
        return true;
    }
};

class TetrisGame {
private:
    Piece* currentPiece;
    int field[M][N] = {};
    int score;
    int dropInterval;
    clock_t lastDropTime;

public:
    TetrisGame() {
        currentPiece = NULL;
        score = 0;
        dropInterval = 700;
        lastDropTime = clock();
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
            if (x < 0 || x >= N || y >= M || (y >= 0 && field[y][x] != 0)) {
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
            score += 100; 
            for (int row = i; row > 0; row--) {
                for (int col = 0; col < N; col++) {
                    field[row][col] = field[row - 1][col];
                }
            }
            for (int col = 0; col < N; col++) {
                field[0][col] = 0; 
            }
			for(int i=0;i<M;i++) {
				for(int j=0;j<N;j++) {
					cout<<field[i][j]<<" ";
				}
				cout<<endl;
			}
            i++; 
        }
    }
	for(int i=0;i<M;i++) {
		for(int j=0;j<N;j++) {
			cout<<field[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
    update();
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
				update();
                break;
            }
            update();
            delay(10);
        }

        update();
        score += 10; 
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
        currentPiece->rotate();
        if (!check()) {
            for (int i = 0; i < 3; i++) currentPiece->rotate();
        }
        update();
    }

    void update() {
        clearOldPosition();
        drawField();
        currentPiece->draw();
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
        sprintf(scoreText, "Final Score: %d", score);
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
        lastDropTime = clock(); 
    }
}};

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
