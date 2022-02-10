//Copyright Eshwary Mishra 2022

#include <SDL.h>

#include "Player.h"
#include "main.h"

APlayer::APlayer(int x, int y, UTexture* _pawn_texture) : APawn(x, y, _pawn_texture)
{
	//pawn_width = 45;
	//pawn_height = 20;
}


void APlayer::HandleInput(SDL_Event& input_event)
{
	//If a key was pressed
	if (input_event.type == SDL_KEYDOWN && input_event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (input_event.key.keysym.sym)
		{
		case SDLK_LEFT: x_velocity -= DOT_VEL; break;
		case SDLK_RIGHT: x_velocity += DOT_VEL; break;
		}
	}

	//If a key was released
	else if (input_event.type == SDL_KEYUP && input_event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (input_event.key.keysym.sym)
		{
		case SDLK_LEFT: x_velocity += DOT_VEL; break;
		case SDLK_RIGHT: x_velocity -= DOT_VEL; break;
		}
	}
}