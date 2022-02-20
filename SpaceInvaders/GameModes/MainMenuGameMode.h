//Copyright Eshwary Mishra 2022

#pragma once

#include "GameModeBase.h"
#include "Pawn.h"

class UMainMenuGameMode : public UGameModeBase
{
public:

	UMainMenuGameMode();

	virtual void BeginPlay() override;

	virtual void HandleInput(SDL_Event& input_event) override;

	virtual void RenderWorld() override;

private:

	/**Start texture*/
	class UTexture start_texture;

	/**Quit texture*/
	class UTexture quit_texture;

	/**Quit texture*/
	class UTexture copyright_texture;

	/**Selected item index*/
	int selected_item_index;
};