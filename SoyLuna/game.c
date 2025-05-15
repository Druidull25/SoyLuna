#include "game.h"
#include <stdio.h>

GameState gameState;

void Game();

void InitGame()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

	gameState = STATE_TITLE;
	Game();
}

void Game()
{
	Command returnCom;

	while(1)
	switch (gameState)
	{

	case STATE_TITLE:
	{
		returnCom = TitleScreen();
		gameState = STATE_NONE;

		switch (returnCom)
		{
		case COM_PLAY:
			gameState = STATE_INGAME; break;
		case COM_EXIT:
			gameState = STATE_EXIT; break;
		}

		break;
	}

	case STATE_INGAME:
	{
		returnCom = GameScreen();
		gameState = STATE_NONE;

		switch (returnCom)
		{
		case COM_BACK:
			gameState = STATE_TITLE; break;
		case COM_EXIT:
			gameState = STATE_EXIT; break;
		}

		break;
	}

	case STATE_EXIT:
	{
		printf("\n> Exiting...\n");

		return;
	}
		default:
			printf("\n<!!!> gameState error\n");
			return;
	}
}