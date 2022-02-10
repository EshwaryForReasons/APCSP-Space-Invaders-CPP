//Copyright Eshwary Mishra 2022

#include "Pawn.h"

#include "Player.h"
#include "main.h"

APawn::APawn(int x, int y, UTexture* _pawn_texture)
{
	//Set the texture for this
	pawn_texture = _pawn_texture;

	//Initialize the offsets
	x_position = x;
	y_position = y;

	//Initialize the velocity
	x_velocity = 0;

	colliders.resize(11);

	//Set collision box dimesions
	simple_collider.w = pawn_width;
	simple_collider.h = pawn_height;

	colliders[0].w = 6;
	colliders[0].h = 1;

	colliders[1].w = 10;
	colliders[1].h = 1;

	colliders[2].w = 14;
	colliders[2].h = 1;

	colliders[3].w = 16;
	colliders[3].h = 2;

	colliders[4].w = 18;
	colliders[4].h = 2;

	colliders[5].w = 20;
	colliders[5].h = 6;

	colliders[6].w = 18;
	colliders[6].h = 2;

	colliders[7].w = 16;
	colliders[7].h = 2;

	colliders[8].w = 14;
	colliders[8].h = 1;

	colliders[9].w = 10;
	colliders[9].h = 1;

	colliders[10].w = 6;
	colliders[10].h = 1;
}


void APawn::HandleInput(SDL_Event& input_event)
{
	
}

void APawn::MovePlayer(std::vector<SDL_Rect>& otherColliders)
{
	//Move the dot left or right
	x_position += x_velocity;

	ShiftColliders();

	//If the dot collided or went too far to the left or right
	if ((x_position < 0) || (x_position + pawn_width > SCREEN_WIDTH) || Main::GetInstance()->CheckCollision(colliders, otherColliders))
	{
		//Move back
		x_position -= x_velocity;

		ShiftColliders();
	}

	//Move the dot up or down
	y_position += y_velocity;

	ShiftColliders();

	//If the dot collided or went too far up or down
	if ((y_position < 0) || (y_position + pawn_height > SCREEN_HEIGHT) || Main::GetInstance()->CheckCollision(colliders, otherColliders))
	{
		//Move back
		y_position -= y_velocity;

		ShiftColliders();
	}
}

void APawn::Render()
{
	//Show the dot
	pawn_texture->Render(x_position, y_position);
}

void APawn::ShiftColliders()
{
	//The row offset
	int r = 0;

	//Go through the dot's collision boxes
	for (int set = 0; set < colliders.size(); ++set)
	{
		//Center the collision box
		colliders[set].x = x_position + (pawn_width - colliders[set].w) / 2;

		//Set the collision box at its row offset
		colliders[set].y = y_position + r;

		//Move the row offset down the height of the collision box
		r += colliders[set].h;
	}
}