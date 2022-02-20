//Copyright Eshwary Mishra 2022

#include "Pawn.h"

#include "Player.h"
#include "main.h"

APawn::APawn(int x, int y, UTexture* _pawn_texture) : SIObject(x, y, _pawn_texture)
{
	//Set collision box dimesions
	simple_collider.w = object_width;
	simple_collider.h = object_height;
	simple_collider.x = x_position;
	simple_collider.y = y_position;

	lives_remaining = 1;
	max_lives = 1;
}

void APawn::Tick()
{
	
}


void APawn::TakeDamage()
{
	SIObject::TakeDamage();

	lives_remaining--;

	if (lives_remaining <= 0)
	{
		Die();
	}
}

void APawn::Die()
{
	SIObject::Die();

	bIsDead = true;

	Main::GetInstance()->RemoveEntity(this);
}


void APawn::HandleInput(SDL_Event& input_event)
{
	
}

void APawn::MovePlayer()
{
	//Move the dot left or right
	x_position += x_velocity;
	simple_collider.x = x_position;

	//If the dot collided or went too far to the left or right
	if ((x_position < 0) || (x_position + object_width > SCREEN_WIDTH) || Main::GetInstance()->CheckGlobalCollision(&simple_collider))
	{
		//Move back
		x_position -= x_velocity;
		simple_collider.x = x_position;
	}

	//Move the dot up or down
	y_position += y_velocity;
	simple_collider.y = y_position;

	//If the dot collided or went too far up or down
	if ((y_position < 0) || (y_position + object_height > SCREEN_HEIGHT) || Main::GetInstance()->CheckGlobalCollision(&simple_collider))
	{
		//Move back
		y_position -= y_velocity;
		simple_collider.y = y_position;
	}
}