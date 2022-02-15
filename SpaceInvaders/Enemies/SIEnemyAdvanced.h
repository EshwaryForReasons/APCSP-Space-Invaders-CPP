//Copyright Eshwary Mishra 2022

#pragma once

#include "Pawn.h"

class ASIEnemyAdvanced : public APawn
{
public:

	ASIEnemyAdvanced(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick() override;
};

