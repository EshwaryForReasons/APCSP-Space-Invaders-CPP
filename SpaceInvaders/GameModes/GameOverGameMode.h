//Copyright Eshwary Mishra 2022

#pragma once

#include "GameModeBase.h"

class UGameOverGameMode : public UGameModeBase
{
public:

	UGameOverGameMode();

	virtual void BeginPlay() override;
	virtual void HandleInput(SDL_Event& input_event) override;

	virtual void RenderWorld() override;

private:

	/**Start texture*/
	class UTexture replay_texture;

	/**Quit texture*/
	class UTexture quit_texture;

	/**Quit texture*/
	class UTexture copyright_texture;

	/**Selected item index*/
	int selected_item_index;
};

