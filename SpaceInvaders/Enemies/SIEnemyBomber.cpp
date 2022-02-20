//Copyright Eshwary Mishra 2022

#include "SIEnemyBomber.h"
#include "Projectiles/ProjectileBulletEnemy.h"
#include "main.h"

ASIEnemyBomber::ASIEnemyBomber(int x, int y, UTexture* pawn_texture) : ASIEnemyBase(x, y, pawn_texture)
{
	object_width = 70;
	object_height = 40;

	lives_remaining = 4;

	simple_collider.w = object_width;
	simple_collider.h = object_height;
}

void ASIEnemyBomber::Attack()
{
	AProjectileBulletEnemy* projectile = new AProjectileBulletEnemy(x_position + object_width / 2, y_position - 10, &Main::GetInstance()->projectile_bullet_texture, this, 1);

	Main::GetInstance()->AddEntity(projectile);
}