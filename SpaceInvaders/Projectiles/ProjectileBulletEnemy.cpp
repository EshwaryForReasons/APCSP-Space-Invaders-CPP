//Copyright Eshwary Mishra 2022

#include "ProjectileBulletEnemy.h"
#include "main.h"
#include "Player.h"
#include "GameModes/GameModeBase.h"

AProjectileBulletEnemy::AProjectileBulletEnemy(int x, int y, UTexture* object_texture, class SIObject* owner, int bullet_level) : AProjectileBullet(x, y, object_texture, owner, bullet_level)
{
	y_velocity = 3;
}

void AProjectileBulletEnemy::Tick()
{
	hit_item = Main::GetInstance()->CheckGlobalCollision(&simple_collider);

	if (hit_item != Main::GetInstance()->current_game_mode->player)
	{
		hit_item = nullptr;
	}

	MoveProjectile();
}