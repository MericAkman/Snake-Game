#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define WIDTH 20
#define HEIGHT 14

struct Node {
    int x, y;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;
int foodX, foodY, score = 0;
int gameOver = 0;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void Setup() {
    dir = RIGHT;
    score = 0;
    gameOver = 0;

    head = (struct Node*)malloc(sizeof(struct Node));
    head->x = WIDTH / 2;
    head->y = HEIGHT / 2;
    head->next = NULL;
    tail = head;

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void Draw() {
    system("cls");

    // Üst sýnýr
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");  // Sol sýnýr

        for (int j = 0; j < WIDTH; j++) {
            char ch = ' ';


            if (i == foodY && j == foodX) {
                ch = 'A';
            }
            else {
                struct Node* temp = head;
                while (temp != NULL) {
                    if (temp->x == j && temp->y == i) {
                        ch = (temp == head) ? 'O' : 'o';
                        break;
                    }
                    temp = temp->next;
                }
            }

            printf("%c", ch);
        }

        printf("#\n");
    }


    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void AddHead(int x, int y) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = head;
    head = newNode;
}

void RemoveTail() {
    if (head == tail) return;
    struct Node* temp = head;
    while (temp->next != tail) {
        temp = temp->next;
    }
    free(tail);
    tail = temp;
    tail->next = NULL;
}

void Logic() {
    int newX = head->x;
    int newY = head->y;

    switch (dir) {
        case LEFT:  newX--; break;
        case RIGHT: newX++; break;
        case UP:    newY--; break;
        case DOWN:  newY++; break;
        default: break;
    }

    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) {
        gameOver = 1;
        return;
    }


    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->x == newX && temp->y == newY) {
            gameOver = 1;
            return;
        }
        temp = temp->next;
    }

    AddHead(newX, newY);

    if (newX == foodX && newY == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }
    else {
        RemoveTail();
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    printf("Game Over! Final Score: %d\n", score);
    getchar();
    return 0;
}


