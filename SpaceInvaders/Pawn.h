//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>

#include "SDLUtilities/Texture.h"
#include "SIObject.h"

class APawn : public SIObject
{
public:

	APawn(int x, int y, UTexture* pawn_texture);

	/**Called every frame*/
	virtual void Tick();


	/**Take damage*/
	virtual void TakeDamage() override;

	/**The death logic*/
	virtual void Die() override;


	/**The amount of lives the player has remaining*/
	int lives_remaining;

	/**Max lives*/
	int max_lives;


	/**Are we dead*/
	bool bIsDead;


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event);

	/**Moves the player and checks collision*/
	virtual void MovePlayer();

protected:

	static const int PAWN_VELOCITY = 2;
};

