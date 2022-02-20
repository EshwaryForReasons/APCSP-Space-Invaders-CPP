//Copyright Eshwary Mishra 2022

#include "MainMenuGameMode.h"

#include "Player.h"
#include "Enemies/SIEnemyBasic.h"
#include "Enemies/SIEnemyIntermediate.h"
#include "Enemies/SIEnemyAdvanced.h"
#include "Enemies/SIEnemyBomber.h"
#include "main.h"

UMainMenuGameMode::UMainMenuGameMode()
{
	selected_item_index = 0;
}

void UMainMenuGameMode::BeginPlay()
{
	UGameModeBase::BeginPlay();

	start_texture.LoadFromRenderedText("START", {255, 255, 255}, EFontSize::FS_TITLE);
	quit_texture.LoadFromRenderedText("QUIT", {255, 255, 255}, EFontSize::FS_TITLE);
	copyright_texture.LoadFromRenderedText("Copyright Eshwary Mishra 2022", {255, 255, 255}, EFontSize::FS_SMALL);
}

void UMainMenuGameMode::HandleInput(SDL_Event& input_event)
{
	UGameModeBase::HandleInput(input_event);

	if (input_event.type == SDL_KEYDOWN && input_event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (input_event.key.keysym.sym)
		{
		case SDLK_UP: selected_item_index = 0; break;
		case SDLK_DOWN: selected_item_index = 1; break;
		case SDLK_RETURN:
			if (selected_item_index == 0)
			{
				Main::GetInstance()->ChangeGameState(EGameState::GS_MainGame);
			}
			else
			{
				Main::GetInstance()->quit = true;
			}
			break;
		}
	}
}


void UMainMenuGameMode::RenderWorld()
{
	const int player_y = SCREEN_HEIGHT * 0.1 + Main::GetInstance()->space_invaders_logo_texture.GetHeight();

	Main::GetInstance()->space_invaders_logo_texture.Render((SCREEN_WIDTH / 2) - (Main::GetInstance()->space_invaders_logo_texture.GetWidth() / 2), SCREEN_HEIGHT * 0.1);

	Main::GetInstance()->player_texture.Render((SCREEN_WIDTH / 2) - (SCREEN_WIDTH * 0.13), player_y + SCREEN_WIDTH * (selected_item_index == 0 ? 0.1 : 0.15));

	start_texture.Render((SCREEN_WIDTH / 2) - (SCREEN_WIDTH * 0.05), player_y + SCREEN_WIDTH * 0.1);
	quit_texture.Render((SCREEN_WIDTH / 2) - (SCREEN_WIDTH * 0.05), player_y + SCREEN_WIDTH * 0.15);

	copyright_texture.Render(10, SCREEN_HEIGHT - copyright_texture.GetHeight() - 10);
}