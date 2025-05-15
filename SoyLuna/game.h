#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "grid.h"
#include "question.h"
#include "config.h"
#include "utils.h"

typedef enum GameState {
	STATE_NONE,
	STATE_TITLE,
	STATE_INGAME,
	STATE_GAMEOVER,
	STATE_EXIT
} GameState;

typedef enum Command {
	COM_NONE,
	COM_PLAY,
	COM_BACK,
	COM_EXIT
} Command;

void InitGame();

Command TitleScreen();
Command GameScreen();

#endif