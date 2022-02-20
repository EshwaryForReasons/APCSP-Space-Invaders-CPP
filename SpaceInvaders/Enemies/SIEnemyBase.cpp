//Copyright Eshwary Mishra 2022

#include "SIEnemyBase.h"

#include "main.h"
#include "GameModes/MainGameMode.h"

ASIEnemyBase::ASIEnemyBase(int x, int y, UTexture* pawn_texture) : APawn(x, y, pawn_texture)
{
	death_score = 100;
	lives_remaining = 1;

	x_velocity = object_width;
	y_velocity = object_height;
}

void ASIEnemyBase::Tick()
{

}


void ASIEnemyBase::TakeDamage()
{
	APawn::TakeDamage();
}

void ASIEnemyBase::Die()
{
	if (bIsDead)
	{
		return;
	}

	Main::GetInstance()->current_game_mode->AddScore(death_score);
	Main::GetInstance()->current_game_mode->AddDeath(1, this);

	APawn::Die();
}


bool ASIEnemyBase::CheckHorizontalMovementPossible(bool bMoveLeft)
{
	if (bMoveLeft && x_position < object_width)
	{
		return false;
	}
	else if (!bMoveLeft && x_position + object_width > SCREEN_WIDTH - object_width * 2)
	{
		return false;
	}

	return true;
}

void ASIEnemyBase::MoveEnemy(bool bMoveX, int _x_velocity)
{
	if (bMoveX)
	{
		//Move the dot left or right
		x_position += _x_velocity;
		simple_collider.x = x_position;
	}
	else
	{
		//Move the dot up or down
		y_position += y_velocity;
		simple_collider.y = y_position;

		//If the dot collided or went too far up or down
		if ((y_position < 0) || (y_position + object_height > SCREEN_HEIGHT) || Main::GetInstance()->CheckGlobalCollision(&simple_collider))
		{
			//Move back
			y_position -= y_velocity;
			simple_collider.y = y_position;
		}
	}
}


void ASIEnemyBase::Attack()
{

}