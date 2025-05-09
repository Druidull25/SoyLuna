#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "grid.h"

#define PLAYER_SIZE 10
#define PLAYER_SPEED 125.0f
#define PLAYER_SPRINT_SPEED 275.0f
#define PLAYER_COLOR RED

typedef struct Player {

	Vector2 position;
	Vector2 dimensions;

	float speed;
	float sprint_speed;

	Color color;

} Player;

Player MakePlayer();

#endif
