//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>

#include "SDLUtilities/Texture.h"

class APawn
{
	public:

	APawn(int x, int y, UTexture* pawn_texture);

	/**The amount of lives the player has remaining*/
	int lives_remainaing;


	/**Handlers user input*/
	virtual void HandleInput(SDL_Event& input_event);

	/**Moves the player and checks collision*/
	void MovePlayer(std::vector<SDL_Rect>& other_colliders);

	/**Renders the player on the screen*/
	void Render();


	//Returns the collision boxes
	std::vector<SDL_Rect>& GetColliders() {return colliders;};

protected:

	static const int DOT_VEL = 2;

	int pawn_width = 40;
	int pawn_height = 20;


	/**The X offset of the player*/
	int x_position;

	/**The Y offset of the player*/
	int y_position;

	/**The Y velocity of the player*/
	int x_velocity;

	/**The Y velocity of the player*/
	int y_velocity;

	/**The player's colliders*/
	std::vector<SDL_Rect> colliders;

	/**The texture of the pawn*/
	UTexture* pawn_texture;

	/**Moves the collision boxes relative to the dot's offset*/
	void ShiftColliders();
};

