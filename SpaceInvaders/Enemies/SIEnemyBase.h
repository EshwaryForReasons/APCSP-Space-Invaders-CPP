//Copyright Eshwary Mishra 2022

#pragma once

#include "Pawn.h"

class ASIEnemyBase : public APawn
{
public:

	ASIEnemyBase(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick() override;


	/**Take damage*/
	virtual void TakeDamage() override;

	/**The death logic*/
	virtual void Die() override;

	bool CheckHorizontalMovementPossible(bool bMoveLeft);
	void MoveEnemy(bool bMoveX, int x_velocity);

	virtual void Attack();

protected:

	/**The points awarded for killing this enemy*/
	int death_score;
};

