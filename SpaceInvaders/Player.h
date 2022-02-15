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


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event) override;

protected:

	/**Spawns a projectile*/
	void SpawnProjectile();

	/**Creates the player HUD*/
	void CreatePlayerHUD();
};