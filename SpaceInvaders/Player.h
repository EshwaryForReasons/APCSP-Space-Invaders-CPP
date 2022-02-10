//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>

#include "pawn.h"
#include "SDLUtilities/Texture.h"

class APlayer : public APawn
{
public:

	APlayer(int x, int y, UTexture* pawn_texture);

	/**The amount of lives the player has remaining*/
	int lives_remainaing;


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event) override;
};

