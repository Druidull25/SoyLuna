#include "player.h"
#include "grid.h"
#include "config.h"

Player MakePlayer()
{
	return (Player) {
		.position = (Vector2){ 0, 0 },
			.dimensions = (Vector2){ PLAYER_SIZE, PLAYER_SPEED },
			.speed = PLAYER_SPEED,
			.sprint_speed = PLAYER_SPRINT_SPEED,
			.color = PLAYER_COLOR,
	};
}

/*void MovePlayer(Player* p)
{
	Vector2 previousPos = p->position;

	UpdateGrid(p, 0);

	float speed = p->speed * GetFrameTime();

	if (IsKeyDown(CONTROL_UP)) p->y -= speed;
	if (IsKeyDown(CONTROL_DOWN)) p->y += speed;
	if (IsInWall(p->x, p->y))
		*playerY = tY;

	if (IsKeyDown(CONTROL_LEFT)) *playerX -= speed;
	if (IsKeyDown(CONTROL_RIGHT)) *playerX += speed;
	if (IsInWall(*playerX, p->y))
		*playerX = tX;

	UpdateGrid(*playerX, p->y, 1);
}*/