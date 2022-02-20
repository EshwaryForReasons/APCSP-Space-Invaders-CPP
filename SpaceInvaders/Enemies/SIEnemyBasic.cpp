//Copyright Eshwary Mishra 2022

#include "SIEnemyBasic.h"

ASIEnemyBasic::ASIEnemyBasic(int x, int y, UTexture* pawn_texture) : ASIEnemyBase(x, y, pawn_texture)
{
	object_width = 45;
	object_height = 40;

	lives_remaining = 1;

	simple_collider.w = object_width;
	simple_collider.h = object_height;
}