#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Block playGrid[GRID_LENGTH][GRID_WIDTH];

char level_filenames[10][100] = {
	"layoutfile.dat",
	"level1.dat",
	"level2.dat",
	"level3.dat",
	"level4.dat",
	"level5.dat",
	"level6.dat",
	"level7.dat",
	"level8.dat",
	"level9.dat",
};

char quiz_filenames[10][100] = {
	"test.bin",
	"level1.dat",
	"level2.dat",
	"level3.dat",
	"level4.dat",
	"level5.dat",
	"level6.dat",
	"level7.dat",
	"level8.dat",
	"level9.dat",
};

void MovePlayer(float* playerX, float* playerY, float speed)
{
	float tX = *playerX;
	float tY = *playerY;

	UpdateGrid(playGrid, *playerX, *playerY, 0);

	speed = speed * GetFrameTime();

	if (IsKeyDown(CONTROL_UP)) *playerY -= speed;
	if (IsKeyDown(CONTROL_DOWN)) *playerY += speed;
	if (IsInWall(playGrid, *playerX, *playerY))
		*playerY = tY;

	if (IsKeyDown(CONTROL_LEFT)) *playerX -= speed;
	if (IsKeyDown(CONTROL_RIGHT)) *playerX += speed;
	if (IsInWall(playGrid, *playerX, *playerY))
		*playerX = tX;

	UpdateGrid(playGrid, *playerX, *playerY, 1);
}

void InitGrid()
{
	for (int i = 0; i < GRID_LENGTH; ++i)
		for (int j = 0; j < GRID_WIDTH; ++j)
		{
			playGrid[i][j] = 0;
		}
}

void UserDraw()
{
	if (!IsInGrid(GetMouseX(), GetMouseY()))
		return;

	if(IsMouseButtonDown(1))
		*MapToGrid(playGrid, GetMouseX(), GetMouseY()) = 0;

	if (IsMouseButtonDown(0))
	{
		*MapToGrid(playGrid, GetMouseX(), GetMouseY()) = 2;

		if(IsKeyDown(CONTROL_DRAWDOOR))
			*MapToGrid(playGrid, GetMouseX(), GetMouseY()) = 3;

		if(IsKeyDown(CONTROL_DRAWGOAL))
			*MapToGrid(playGrid, GetMouseX(), GetMouseY()) = 4;

		if (IsKeyDown(CONTROL_DRAWNPC))
			*MapToGrid(playGrid, GetMouseX(), GetMouseY()) = 5;
	}
}

Block* ClosestToPlayer(float playerX, float playerY)
{
	int dirX[] = { 0, 1, -1, 0, 0, 1, -1, 1, -1};
	int dirY[] = { 0, 0, 0, 1, -1, 1, -1, -1, 1};

	int gridX = playerX / GRID_CELL_SIZE;
	int gridY = playerY / GRID_CELL_SIZE;
	int a, b, c, min_dist, min_index;
	int newX, newY;

	min_dist = INT_MAX;
	min_index = 0;

	for (int i = 1; i <= 8; ++i)
	{
		newX = gridX + dirX[i];
		newY = gridY + dirY[i];

		if (newX < 0 || newX >= GRID_LENGTH) continue;
		if (newY < 0 || newY >= GRID_WIDTH) continue;

		if (playGrid[newX][newY] <= 2) continue;

		a = playerX - newX * GRID_CELL_SIZE - GRID_CELL_SIZE / 2;
		b = playerY - newY * GRID_CELL_SIZE - GRID_CELL_SIZE / 2;

		c = a * a + b * b;
		if(c < min_dist)
		{ 
			min_dist = c;
			min_index = i;
		}
	}

	gridX += dirX[min_index];
	gridY += dirY[min_index];

	return &playGrid[gridX][gridY];
}

int GetInteraction(float playerX, float playerY)
{
	int block = *ClosestToPlayer(playerX, playerY);

	if(IsKeyDown(CONTROL_INTERACT))
		return block;

	return 0;
}

void clearGrid() {
	for (int i = 0; i < GRID_LENGTH; ++i) {
		for (int j = 0; j < GRID_WIDTH; ++j) {
			playGrid[i][j] = 0;
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

	int interaction = 0, quizActive = 0, level = 0, quiz_question = 0, scor = 0, quiz_number;

	InitQuestions();
	QUESTION* questions = LoadQuiz(quiz_filenames[level], &quiz_number);
	InitGrid();

	LoadGameLayout(playGrid, &playerX, &playerY, level_filenames[level]);

	Command nextCom = COM_EXIT;
	while (!WindowShouldClose())
	{
		if (ButtonClicked(backButton))
		{
			nextCom = COM_BACK;
			break;
		}

		if (ButtonClicked(saveButton))
			SaveGameLayout(playGrid, &playerX, &playerY);

		if (ButtonClicked(loadButton))
			LoadGameLayout(playGrid, &playerX, &playerY, level_filenames[level]);

		interaction = GetInteraction(playerX, playerY);

		switch (interaction)
		{
		case 3:
			if (quiz_question < quiz_number) 
				//cap pentru nr de intrebari / nivel
				quizActive = 1;
			break;
		case 5:
			break;
		}

		if (!quizActive)
		{
			UserDraw();

			if (IsKeyDown(CONTROL_SPRINT))
				speed = 250.0f;
			else
				speed = 125.0f;


			MovePlayer(&playerX, &playerY, speed);
		}

		BeginDrawing();
		ClearBackground(backgroundColor);

		GameDrawGrid(playGrid, startingCell);
		DrawRectangle(playerX, playerY, PLAYER_SIZE, PLAYER_SIZE, RED);

		if (*ClosestToPlayer(playerX, playerY) == 5)
			DrawText("?", playerX + 2, playerY - 35, 30, RED);

		DrawButton(backButton);
		DrawButton(saveButton);
		DrawButton(loadButton);

		if (interaction == 5)
		{
			DrawTextBox((Rectangle) {
				.x = 20,
				.y = 20,
				.width = 1200,
				.height = 600,
			}, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque orci eros, pulvinar nec lectus id, auctor semper nisi. Cras eget convallis arcu. Etiam ac nisl auctor, varius velit quis, malesuada odio. Ut id mauris sed enim ullamcorper eleifend. Nunc in mi quis velit ultrices sollicitudin. Maecenas dapibus consectetur nunc, in euismod eros fringilla id. Maecenas molestie, neque sed suscipit rutrum, sem dolor laoreet justo, eget bibendum felis elit sit amet urna. Sed tempor vulputate dolor rutrum fringilla. Donec in elementum neque. Fusce et maximus enim. Vivamus nibh turpis, aliquet quis tristique ut, tincidunt non orci. Duis sollicitudin nunc ac est vestibulum auctor. Mauris imperdiet libero nisi.In massa mauris, fermentum ultricies sodales a, placerat vitae sapien. Mauris imperdiet justo vel elit elementum, non bibendum ex malesuada. asdjlkkadls kljadslkjdas ");
		}

		if (quizActive) {
			if (Quiz(questions[quiz_question]) == 1){ //raspunde corect
				quizActive = 0;
				quiz_question++;
				scor++;
				printf("intrebari: %d\n", quiz_question);
				*ClosestToPlayer(playerX, playerY) = 2; //disable quiz block

			}
			else if (Quiz(questions[quiz_question]) == 2) { //raspunde gresit
				quiz_question++;
				quizActive = 0;
				printf("intrebari: %d\n", quiz_question);

				*ClosestToPlayer(playerX, playerY) = 2; //disable quiz block

			}
		}

		if (quiz_question == quiz_number) {
			quiz_question = 0;
			level++;
			clearGrid();
			playerX = 0;
			playerY = 0;
			LoadGameLayout(playGrid, &playerX, &playerY, level_filenames[level]); //next level
			free(questions); //stop memory leaks
			QUESTION* questions = LoadQuiz(quiz_filenames[level], &quiz_number); //next quiz

		}

		EndDrawing();
	}
	free(questions);

	return nextCom;
}