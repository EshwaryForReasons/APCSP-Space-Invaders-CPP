//Copyright Eshwary Mishra 2022

#include "SIEnemyBasic.h"

ASIEnemyBasic::ASIEnemyBasic(int x, int y, UTexture* pawn_texture) : APawn(x, y, pawn_texture)
{
	object_width = 45;
	object_height = 40;

	simple_collider.w = object_width;
	simple_collider.h = object_height;
}

void ASIEnemyBasic::Tick()
{
	APawn::Tick();
}