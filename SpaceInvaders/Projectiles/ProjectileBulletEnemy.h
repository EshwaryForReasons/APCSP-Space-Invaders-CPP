//Copyright Eshwary Mishra 2022

#pragma once

#include "ProjectileBullet.h"

class AProjectileBulletEnemy : public AProjectileBullet
{
public:

	AProjectileBulletEnemy(int x, int y, UTexture* object_texture, class SIObject* owner, int bullet_level);

	virtual void Tick() override;
};

