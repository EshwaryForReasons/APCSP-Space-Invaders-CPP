//Copyright Eshwary Mishra 2022

#pragma once

#include "Pawn.h"

class ASIEnemyBomber : public APawn
{
public:

	ASIEnemyBomber(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick() override;
};

