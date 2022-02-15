//Copyright Eshwary Mishra 2022

#pragma once

#include "Pawn.h"

class ASIEnemyBasic : public APawn
{
public:

	ASIEnemyBasic(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick() override;
};

