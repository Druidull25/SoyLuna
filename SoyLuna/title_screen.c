#include "game.h"
#include <stdio.h>

Command TitleScreen()
{
	Color backgroundColor = RAYWHITE;

	Text titleText = {
		.text = "Sex Maze",
		.color = DARKGRAY,
		.size = 50,
	};
	titleText.x = SCREEN_WIDTH/2 - MeasureText(titleText.text, titleText.size)/2;
	titleText.y = 50;

	Button playButton = MakeButton((Rectangle) { 0, 210, 120, 50 }, 0.3, "Play", 30);
	playButton.rectangle.x = SCREEN_WIDTH / 2 - playButton.rectangle.width / 2;

	Button quitButton = MakeButton((Rectangle) { 0, 290, 120, 50 }, 0.3, "Quit", 30);
	quitButton.rectangle.x = SCREEN_WIDTH / 2 - quitButton.rectangle.width / 2;

	while (!WindowShouldClose())
	{

		if(ButtonClicked(quitButton))
			return COM_EXIT;
		if(ButtonClicked(playButton))
			return COM_PLAY;


		BeginDrawing();
		
		ClearBackground(backgroundColor);

		DrawTextS(titleText);
		
		DrawButton(playButton);
		DrawButton(quitButton);

		EndDrawing();
	}

	return COM_EXIT;
}