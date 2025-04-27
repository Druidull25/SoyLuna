#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

typedef struct NODE{
    int data;
    struct NODE *leftChild;
    struct NODE *rightChild;
}NODE;


int main(void)
{
    InitWindow(800, 450, "Raylib Window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}