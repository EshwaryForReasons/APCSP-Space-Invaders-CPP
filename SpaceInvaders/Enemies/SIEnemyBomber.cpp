//Copyright Eshwary Mishra 2022

#include "SIEnemyBomber.h"

ASIEnemyBomber::ASIEnemyBomber(int x, int y, UTexture* pawn_texture) : APawn(x, y, pawn_texture)
{
	object_width = 70;
	object_height = 40;

	simple_collider.w = object_width;
	simple_collider.h = object_height;
}

void ASIEnemyBomber::Tick()
{
	APawn::Tick();
}