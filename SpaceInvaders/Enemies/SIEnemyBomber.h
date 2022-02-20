//Copyright Eshwary Mishra 2022

#pragma once

#include "SIEnemyBase.h"

class ASIEnemyBomber : public ASIEnemyBase
{
public:

	ASIEnemyBomber(int x, int y, UTexture* pawn_texture);

	virtual void Attack() override;
};

