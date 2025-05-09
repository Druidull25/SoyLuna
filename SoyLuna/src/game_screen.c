#include "game.h"

#define GRID_LENGTH 30
#define GRID_WIDTH 20

unsigned int playGrid[GRID_LENGTH][GRID_WIDTH];

void DrawGrid(Rectangle cell)
{
	Color cellColor[] = { RAYWHITE, SKYBLUE, MAGENTA };
	int n = sizeof(cellColor) / sizeof(cellColor[0]);

	for (int i = 0; i < GRID_LENGTH; ++i)
	for (int j = 0; j < GRID_WIDTH; ++j)
	{
		if (playGrid[i][j] >= n) continue;

		DrawRectangle(cell.x + i * cell.width, cell.y + j * cell.height,
			cell.width, cell.height, cellColor[playGrid[i][j]]);
	}
}

void MovePlayer(int* playerX, int* playerY)
{
	playGrid[*playerX][*playerY] = 0;

	if (IsKeyPressed(CONTROL_UP)) *playerY -= 1;
	if (IsKeyPressed(CONTROL_DOWN)) *playerY += 1;
	if (IsKeyPressed(CONTROL_LEFT)) *playerX -= 1;
	if (IsKeyPressed(CONTROL_RIGHT)) *playerX += 1;

	if (*playerX < 0) *playerX = 0;
	if (*playerX >= GRID_LENGTH) *playerX = GRID_LENGTH - 1;
	if (*playerY < 0) *playerY = 0;
	if (*playerY >= GRID_WIDTH) *playerY = GRID_WIDTH - 1;

	playGrid[*playerX][*playerY] = 1;
}

void InitGrid()
{
	for (int i = 0; i < GRID_LENGTH; ++i)
	for (int j = 0; j < GRID_WIDTH; ++j)
	{
		playGrid[i][j] = 0;
	}
}

Command GameScreen()
{
	Color backgroundColor = BLACK;

	Button backButton = MakeButton((Rectangle) { 650, 350, 120, 50 }, 0.3, "Back", 30);

	Rectangle startingCell = {
		.x = 30,
		.y = 12,
		.width = 20,
		.height = 20
	};

	int playerX = 0;
	int playerY = 0;

	InitGrid();

	while (!WindowShouldClose())
	{
		if (ButtonClicked(backButton))
			return COM_BACK;

		MovePlayer(&playerX, &playerY);

		BeginDrawing();
		ClearBackground(backgroundColor);

		DrawButton(backButton);
		DrawGrid(startingCell);

		EndDrawing();
	}

	return COM_EXIT;
}