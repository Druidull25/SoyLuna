#ifndef GRID_H
#define GRID_H

#include "raylib.h"

#define GRID_LENGTH 50
#define GRID_WIDTH 28
#define GRID_CELL_SIZE 25

#define PLAYER_SIZE 20

typedef enum Block {
	EMPTY,
	PLAYER,
	BLOCK,
	QUIZ,
	CEVA,
	INFO
} Block;

void GameDrawGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], Rectangle cell);
int* MapToGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], int x, int y);
int IsInGrid(float x, float y);
int IsInWall(Block playGrid[GRID_LENGTH][GRID_WIDTH], float playerX, float playerY);
void UpdateGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], float playerX, float playerY, int value);

void LoadGameLayout(Block playGrid[GRID_LENGTH][GRID_WIDTH], float* playerX, float* playerY, char fisier_nivel[100]);
void SaveGameLayout(Block playGrid[GRID_LENGTH][GRID_WIDTH], float* playerX, float* playerY);

#endif