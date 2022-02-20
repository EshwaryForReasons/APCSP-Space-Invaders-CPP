//Copyright Eshwary Mishra 2022

#pragma once

#include <memory>

#include "SIObject.h"

class AProjectileBullet : public SIObject
{
public:

	AProjectileBullet(int x, int y, UTexture* object_texture, class SIObject* owner, int bullet_level);

	/**Called every frame*/
	virtual void Tick() override;

	void MoveProjectile();

	/**Called when the projectile hits something*/
	virtual void OnHit(bool bOffScreen);

protected:

	/**The thing this projectile hit*/
	class SIObject* hit_item;

	/**The pawn that owns this projectile*/
	class SIObject* owner;

	/**The level of this bullet*/
	int bullet_level;
};