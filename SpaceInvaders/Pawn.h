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
	void TakeDamage();

	/**The death logic*/
	void Die();


	/**The amount of lives the player has remaining*/
	int lives_remaining;

	/**Max lives*/
	int max_lives;


	/**True if bullet exists*/
	bool bHasBullet;


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event);

	/**Moves the player and checks collision*/
	virtual void MovePlayer();

protected:

	static const int PAWN_VELOCITY = 2;
};

