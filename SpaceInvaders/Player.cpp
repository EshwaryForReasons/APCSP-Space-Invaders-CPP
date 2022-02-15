//Copyright Eshwary Mishra 2022

#include <SDL.h>

#include "Player.h"
#include "main.h"
#include "Projectiles/ProjectileBullet.h"

APlayer::APlayer(int x, int y, UTexture* _pawn_texture) : APawn(x, y, _pawn_texture)
{
	object_width = 45;
	object_height = 40;

	simple_collider.w = object_width;
	simple_collider.h = object_height;

	lives_remaining = 3;
}

void APlayer::Tick()
{
	APawn::Tick();

	MovePlayer();

	CreatePlayerHUD();
}


void APlayer::HandleInput(SDL_Event& input_event)
{
	//If a key was pressed
	if (input_event.type == SDL_KEYDOWN && input_event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (input_event.key.keysym.sym)
		{
		case SDLK_LEFT: x_velocity -= PAWN_VELOCITY; break;
		case SDLK_RIGHT: x_velocity += PAWN_VELOCITY; break;
		case SDLK_SPACE: SpawnProjectile(); break;
		}
	}

	//If a key was released
	else if (input_event.type == SDL_KEYUP && input_event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (input_event.key.keysym.sym)
		{
		case SDLK_LEFT: x_velocity += PAWN_VELOCITY; break;
		case SDLK_RIGHT: x_velocity -= PAWN_VELOCITY; break;
		}
	}
}


void APlayer::SpawnProjectile()
{
	if (!bHasBullet)
	{
		std::shared_ptr<AProjectileBullet> projectile = std::make_shared<AProjectileBullet>(x_position + object_width / 2, y_position - 10, &Main::GetInstance()->projectile_bullet_texture, this);

		Main::GetInstance()->AddEntity(projectile);

		bHasBullet = true;
	}
}


void APlayer::CreatePlayerHUD()
{
	for (int i = 1; i <= lives_remaining; i++)
	{
		Main::GetInstance()->heart_texture.Render(SCREEN_WIDTH - (Main::GetInstance()->heart_texture.GetWidth() * i) - 10, SCREEN_HEIGHT - Main::GetInstance()->heart_texture.GetHeight() - 10);
	}
}