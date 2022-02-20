//Copyright Eshwary Mishra 2022

#include <SDL.h>

#include "Player.h"
#include "main.h"
#include "Projectiles/ProjectileBullet.h"
#include "GameModes/MainGameMode.h"
#include "SDLUtilities/Texture.h"

APlayer::APlayer(int x, int y, UTexture* _pawn_texture) : APawn(x, y, _pawn_texture)
{
	object_width = 45;
	object_height = 40;

	simple_collider.w = object_width;
	simple_collider.h = object_height;

	lives_remaining = 3;

	bullet_level = 0;

	bullet_upgrade_texture.LoadFromRenderedText("U - UPGRADE BULLET: $500", {255, 255, 255}, EFontSize::FS_SMALL);
	buy_life_texture.LoadFromRenderedText("L - BUY LIFE: $1500", {255, 255, 255}, EFontSize::FS_SMALL);
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
		case SDLK_u: UpgradeBullet(); break;
		case SDLK_l: BuyLife(); break;
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


void APlayer::Die()
{
	APawn::Die();

	Main::GetInstance()->ChangeGameState(EGameState::GS_GameOver);
}


void APlayer::UpgradeBullet()
{
	if (bullet_level == 0 && Main::GetInstance()->current_game_mode->player_money >= 500)
	{
		Main::GetInstance()->current_game_mode->player_money -= 500;
		bullet_level = 1;
		bullet_upgrade_texture.LoadFromRenderedText("U - UPGRADE BULLET: $1350", {255, 255, 255}, EFontSize::FS_SMALL);
	}
	else if (bullet_level == 1 && Main::GetInstance()->current_game_mode->player_money >= 1350)
	{
		Main::GetInstance()->current_game_mode->player_money -= 1350;
		bullet_level = 2;
		bullet_upgrade_texture.LoadFromRenderedText("U - UPGRADE BULLET: $9000", {255, 255, 255}, EFontSize::FS_SMALL);
	}
	else if (bullet_level == 2 && Main::GetInstance()->current_game_mode->player_money >= 9000)
	{
		Main::GetInstance()->current_game_mode->player_money -= 9000;
		bullet_level = 3;
		bullet_upgrade_texture.LoadFromRenderedText("U - UPGRADE BULLET: MAX", {255, 255, 255}, EFontSize::FS_SMALL);
	}
}

void APlayer::BuyLife()
{
	if (lives_remaining < 3 && Main::GetInstance()->current_game_mode->player_money >= 1500)
	{
		lives_remaining++;
	}
}


void APlayer::SpawnProjectile()
{
	AProjectileBullet* projectile = new AProjectileBullet(x_position + object_width / 2, y_position - 10, &Main::GetInstance()->projectile_bullet_texture, this, bullet_level);

	Main::GetInstance()->AddEntity(projectile);
}


void APlayer::CreatePlayerHUD()
{
	for (int i = 1; i <= lives_remaining; i++)
	{
		Main::GetInstance()->heart_texture.Render(SCREEN_WIDTH - (Main::GetInstance()->heart_texture.GetWidth() * i) - 10, SCREEN_HEIGHT - Main::GetInstance()->heart_texture.GetHeight() - 10);
	}

	if (score_texture.LoadFromRenderedText("$" + std::to_string(Main::GetInstance()->current_game_mode->player_money), {255, 255, 255}, EFontSize::FS_NORMAL))
	{
		score_texture.Render(10, SCREEN_HEIGHT - score_texture.GetHeight() - 40);
	}

	if (score_texture.LoadFromRenderedText("SCORE: " + std::to_string(Main::GetInstance()->current_game_mode->player_score), {255, 255, 255}, EFontSize::FS_NORMAL))
	{
		score_texture.Render(10, SCREEN_HEIGHT - score_texture.GetHeight() - 10);
	}

	bullet_upgrade_texture.Render(SCREEN_WIDTH / 2 - (bullet_upgrade_texture.GetWidth() - 20), SCREEN_HEIGHT - 35);
	buy_life_texture.Render(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT - 35);
}