//Copyright Eshwary Mishra 2022

#pragma once

#include "SIEnemyBase.h"

class ASIEnemyAdvanced : public ASIEnemyBase
{
public:

	ASIEnemyAdvanced(int x, int y, UTexture* pawn_texture);

	virtual void Attack() override;
};

