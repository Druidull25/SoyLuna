#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define GRID_LENGTH 50
#define GRID_WIDTH 28
#define GRID_CELL_SIZE 25

#define PLAYER_SIZE 20.0

Block playGrid[GRID_LENGTH][GRID_WIDTH];

Question q;

void SaveGameLayout(float* playerX, float* playerY) {
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

void LoadGameLayout(float* playerX, float* playerY)
{
	FILE* MapInputFile;
	if ((MapInputFile = fopen(FILENAME_LEVEL, "rb")) == NULL) {
		printf("\n <!!!> Nu poate fi deschis fisierul \"%s\"\n", FILENAME_LEVEL);
		return;
	}

	fread(playerX, sizeof(playerX), 1, MapInputFile);
	fread(playerY, sizeof(playerY), 1, MapInputFile);
	fread(playGrid, sizeof(Block), GRID_LENGTH * GRID_WIDTH, MapInputFile);

	fclose(MapInputFile);
}

void DrawGameGrid(Rectangle cell)
{
	Color cellColor[] = { RAYWHITE, SKYBLUE, MAGENTA, GREEN };
	int n = sizeof(cellColor) / sizeof(cellColor[0]);

	for (int i = 0; i < GRID_LENGTH; ++i)
	for (int j = 0; j < GRID_WIDTH; ++j)
	{
		if (playGrid[i][j] >= n) continue;

		DrawRectangle(cell.x + i * cell.width, cell.y + j * cell.height,
			cell.width, cell.height, cellColor[playGrid[i][j]]);
	}
}

int* MapToGrid(int x, int y)
{
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

int IsInWall(float playerX, float playerY)
{
	int wallCheck = (*MapToGrid(playerX, playerY) == 2) ||
		(*MapToGrid(playerX + PLAYER_SIZE, playerY) == 2) ||
		(*MapToGrid(playerX + PLAYER_SIZE, playerY + PLAYER_SIZE) == 2) ||
		(*MapToGrid(playerX, playerY + PLAYER_SIZE) == 2);

	int hCheck = (playerX < 0 || playerX + PLAYER_SIZE > GRID_LENGTH * GRID_CELL_SIZE);
	int vCheck = (playerY < 0 || playerY + PLAYER_SIZE > GRID_WIDTH * GRID_CELL_SIZE);

	return wallCheck || hCheck || vCheck;
}

void UpdateGrid(float playerX, float playerY, int value)
{
	int X, Y;
	X = playerX;
	Y = playerY;



	if (*MapToGrid(playerX,playerY) != 3)
	{
		*MapToGrid(playerX, playerY) = value;

	}



	if (*MapToGrid(playerX + PLAYER_SIZE, playerY) != 3)
	{
		*MapToGrid(playerX + PLAYER_SIZE, playerY) = value;
	}


	if (*MapToGrid(playerX + PLAYER_SIZE, playerY + PLAYER_SIZE) != 3)
	{
		*MapToGrid(playerX + PLAYER_SIZE, playerY + PLAYER_SIZE) = value;
	}



	if (*MapToGrid(playerX, playerY + PLAYER_SIZE) != 3)
	{
		*MapToGrid(playerX, playerY + PLAYER_SIZE) = value;
	}

	
}

void MovePlayer(float* playerX, float* playerY, float speed)
{
	float tX = *playerX;
	float tY = *playerY;


	UpdateGrid(*playerX, *playerY, 0);


	speed = speed * GetFrameTime();

	if (IsKeyDown(CONTROL_UP)) *playerY -= speed;
	if (IsKeyDown(CONTROL_DOWN)) *playerY += speed;
	if (IsInWall(*playerX, *playerY))
		*playerY = tY;

	if (IsKeyDown(CONTROL_LEFT)) *playerX -= speed;
	if (IsKeyDown(CONTROL_RIGHT)) *playerX += speed;
	if (IsInWall(*playerX, *playerY))
		*playerX = tX;

	UpdateGrid(*playerX, *playerY, 1);
}

void InitGrid()
{
	for (int i = 0; i < GRID_LENGTH; ++i)
	for (int j = 0; j < GRID_WIDTH; ++j)
	{
		playGrid[i][j] = 0;
	}

	strcpy(q.text, "What is the main goal of integrating elements across VR, AR, and MR platforms?\n\nA) Seamless User Experience\n\nB) Increasing Complexity\n\nC) Reducing File Size\n\nD) Enhancing Brightness\n");
	q.ans = 'A';
}

void DrawTextBox(Rectangle box, const char* text)
{
	int padding = 20;
	int wordCount = 0;
	int fontSize = 30;
	const char** words = TextSplit(text, ' ', &wordCount);

	Vector2 pos = { box.x + padding, box.y + padding };

	Color color = { 0, 0, 0, 100 };
	DrawRectangleRec(box, color);

	for (int i = 0; i < wordCount; ++i)
	{
		if (pos.x + MeasureText(TextFormat(" %s", words[i]), fontSize) + padding
			<= box.x + box.width)
		{
			DrawText(words[i], pos.x, pos.y, fontSize, WHITE);
			pos.x += MeasureText(TextFormat(" %s", words[i]), fontSize);
		}
		else
		{
			pos.x = box.x + padding;
			pos.y += fontSize + padding;
		}
	}
}

Command GameScreen()
{
	Color backgroundColor = DARKGRAY;

	Button backButton = MakeButton((Rectangle) { 830, 710, 120, 50 }, 0.3, "Back", 30);
	Button saveButton = MakeButton((Rectangle) { 970, 710, 120, 50 }, 0.3, "Save", 30);
	Button loadButton = MakeButton((Rectangle) { 1110, 710, 120, 50 }, 0.3, "Load", 30);

	Rectangle startingCell = {
		.x = 0,
		.y = 0,
		.width = GRID_CELL_SIZE,
		.height = GRID_CELL_SIZE,
	};

	float playerX = 0;
	float playerY = 0;
	float speed = 125.0f;
	int is_in_ques = 0;

	InitGrid();

	while (!WindowShouldClose())
	{
		if (ButtonClicked(backButton))
			return COM_BACK;

		if (ButtonClicked(saveButton))
			SaveGameLayout(&playerX, &playerY);

		if (ButtonClicked(loadButton))
			LoadGameLayout(&playerX, &playerY);

		if (IsMouseButtonDown(0) && IsInGrid(GetMouseX(), GetMouseY()))
			*MapToGrid(GetMouseX(), GetMouseY()) = 2;
		if (IsMouseButtonDown(1) && IsInGrid(GetMouseX(), GetMouseY()))
			*MapToGrid(GetMouseX(), GetMouseY()) = 0;

		if (IsKeyDown(CONTROL_Q) && IsInGrid(GetMouseX(), GetMouseY()))
			*MapToGrid(GetMouseX(), GetMouseY()) = 3;

		if (IsKeyDown(CONTROL_SPRINT))
			speed = 250.0f;
		else
			speed = 125.0f;

			MovePlayer(&playerX, &playerY, speed);
		

		BeginDrawing();
		ClearBackground(backgroundColor);

		DrawGameGrid(startingCell);
		DrawRectangle(playerX, playerY, PLAYER_SIZE, PLAYER_SIZE, RED);

		DrawButton(backButton);
		DrawButton(saveButton);
		DrawButton(loadButton);

		if (IsKeyDown(CONTROL_SHOWDIALOG) && *MapToGrid(playerX,playerY) == 3)
		{
			DrawTextBox((Rectangle) {
				.x = 20,
				.y = 20,
				.width = 1200,
				.height = 600,
			}, q.text);
		}



		EndDrawing();
	}

	return COM_EXIT;
}