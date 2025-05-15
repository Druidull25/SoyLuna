#include "grid.h"
#include "config.h"
#include <stdio.h>

void GameDrawGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], Rectangle cell)
{
	Color cellColor[] = { RAYWHITE,  RAYWHITE, GRAY, BROWN, GREEN };
	Color currColor;
	int n = sizeof(cellColor) / sizeof(cellColor[0]);

	for (int i = 0; i < GRID_LENGTH; ++i)
		for (int j = 0; j < GRID_WIDTH; ++j)
		{
				
			if (playGrid[i][j] >= n) currColor = MAGENTA;
			else currColor = cellColor[playGrid[i][j]];

			DrawRectangle(cell.x + i * cell.width, cell.y + j * cell.height,
				cell.width, cell.height, currColor);
		}
}

int* MapToGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], int x, int y)
{ //aici se pun blockuri
	int gridX = x / GRID_CELL_SIZE;
	int gridY = y / GRID_CELL_SIZE;

	if (gridX >= GRID_LENGTH) gridX = GRID_LENGTH - 1;
	if (gridY >= GRID_WIDTH) gridY = GRID_WIDTH - 1;

	return &playGrid[gridX][gridY];
}

int IsInGrid(float x, float y)
{
	return (x >= 0 && x <= GRID_LENGTH * GRID_CELL_SIZE) &&
		(y >= 0 && y <= GRID_WIDTH * GRID_CELL_SIZE);
}

int IsInWall(Block playGrid[GRID_LENGTH][GRID_WIDTH], float playerX, float playerY)
{
	int wallCheck = (*MapToGrid(playGrid, playerX, playerY) >= 2) ||
		(*MapToGrid(playGrid, playerX + PLAYER_SIZE, playerY) >= 2) ||
		(*MapToGrid(playGrid, playerX + PLAYER_SIZE, playerY + PLAYER_SIZE) >= 2) ||
		(*MapToGrid(playGrid, playerX, playerY + PLAYER_SIZE) >= 2);

	int hCheck = (playerX < 0 || playerX + PLAYER_SIZE > GRID_LENGTH * GRID_CELL_SIZE);
	int vCheck = (playerY < 0 || playerY + PLAYER_SIZE > GRID_WIDTH * GRID_CELL_SIZE);

	return wallCheck || hCheck || vCheck;
}

void UpdateGrid(Block playGrid[GRID_LENGTH][GRID_WIDTH], float playerX, float playerY, int value)
{
	*MapToGrid(playGrid, playerX, playerY) = value;
	*MapToGrid(playGrid, playerX + PLAYER_SIZE, playerY) = value;
	*MapToGrid(playGrid, playerX + PLAYER_SIZE, playerY + PLAYER_SIZE) = value;
	*MapToGrid(playGrid, playerX, playerY + PLAYER_SIZE) = value;
}

void SaveGameLayout(Block playGrid[GRID_LENGTH][GRID_WIDTH], float* playerX, float* playerY) {
	FILE* MapOutputFile;
	if ((MapOutputFile = fopen(FILENAME_LEVEL, "wb")) == NULL) {
		printf("\n <!!!> Nu poate fi deschis fisierul \"%s\"\n", FILENAME_LEVEL);
		return;
	}

	fwrite(playerX, sizeof(playerX), 1, MapOutputFile);
	fwrite(playerY, sizeof(playerY), 1, MapOutputFile);
	fwrite(playGrid, sizeof(Block), GRID_LENGTH * GRID_WIDTH, MapOutputFile);

	fclose(MapOutputFile);
}

void LoadGameLayout(Block playGrid[GRID_LENGTH][GRID_WIDTH], float* playerX, float* playerY, char fisier_nivel[100])
{
	FILE* MapInputFile;
	if ((MapInputFile = fopen(fisier_nivel, "rb")) == NULL) {
		printf("\n <!!!> Nu poate fi deschis fisierul \"%s\"\n", fisier_nivel);
		return;
	}

	fread(playerX, sizeof(playerX), 1, MapInputFile);
	fread(playerY, sizeof(playerY), 1, MapInputFile);
	fread(playGrid, sizeof(Block), GRID_LENGTH * GRID_WIDTH, MapInputFile);

	fclose(MapInputFile);
}