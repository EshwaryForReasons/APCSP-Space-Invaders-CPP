//Copyright Eshwary Mishra 2022

#pragma once

#include "SIObject.h"

class AProjectileBullet : public SIObject
{
public:

	AProjectileBullet(int x, int y, UTexture* object_texture, class APawn* owner);

	/**Called every frame*/
	virtual void Tick() override;

	void MoveProjectile();

	/**Called when the projectile hits something*/
	void OnHit();

protected:

	/**The thing this projectile hit*/
	class APawn* hit_item;

	/**The pawn that owns this projectile*/
	class APawn* owner;
};