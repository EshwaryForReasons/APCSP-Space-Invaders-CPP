//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>

#include "pawn.h"

class APlayer : public APawn
{
public:

	APlayer(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick() override;

	/**The amount of lives the player has remaining*/
	int lives_remainaing;


	/**The level of the bullet*/
	int bullet_level;


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event) override;


	/**The death logic*/
	virtual void Die() override;

protected:

	/**Score texture*/
	class UTexture score_texture;

	/**Score texture*/
	class UTexture bullet_upgrade_texture;

	/**Score texture*/
	class UTexture buy_life_texture;

	/**Spawns a projectile*/
	void SpawnProjectile();

	/**Creates the player HUD*/
	void CreatePlayerHUD();

	/**Upgrades bullet*/
	void UpgradeBullet();

	/**Buys a life*/
	void BuyLife();
};