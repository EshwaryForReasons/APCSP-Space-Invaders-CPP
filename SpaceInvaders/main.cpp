//Copyright Eshwary Mishra 2022

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "main.h"
#include "player.h"
#include "SIObject.h"
#include "GameModes/MainGameMode.h"
#include "Enemies/SIEnemyBasic.h"

static Main* global_main = nullptr;

static std::string ErrorList = {};

void InsertNewError(std::string Error)
{
	ErrorList.append(Error);

	SI_LOG(Error);
}


Main::Main()
{
	global_main = this;

	global_entities = {};
}

Main::~Main()
{
	global_main = nullptr;
}

Main* Main::GetInstance()
{
	return global_main;
}


void Main::MainTick()
{
	bool quit = false;

	//Create the main game mode
	std::unique_ptr<UMainGameMode> main_game_mode = std::make_unique<UMainGameMode>();
	main_game_mode->InitializeEnemies();

	//Event handler
	SDL_Event event;

	//The player that will be moving around on the screen
	std::shared_ptr<APlayer> player = std::make_shared<APlayer>(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, &Main::GetInstance()->player_texture);

	AddEntity(player);

	int scrolling_offset = 0;

	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			//User requests quit
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle input for the dot
			player->HandleInput(event);
		}

		//Scrolling background
		scrolling_offset++;

		if (scrolling_offset > 1920)
		{
			scrolling_offset = 0;
		}

		//Clear screen
		SDL_SetRenderDrawColor(Main::GetInstance()->global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Main::GetInstance()->global_renderer);

		background_texture.Render(0, scrolling_offset);
		background_texture.Render(0, scrolling_offset - background_texture.GetHeight());

		for (std::shared_ptr<class SIObject> object : global_entities)
		{
			object->Tick();
		}

		for (std::shared_ptr<class SIObject> object : global_entities)
		{
			object->Render();
		}

		//Update screen
		SDL_RenderPresent(Main::GetInstance()->global_renderer);
	}
}


bool Main::InitializeSDL()
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SI_LOG("SDL could not initialize. SDL Error: " << SDL_GetError())

		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			SI_LOG("Warning: Linear texture filtering not enabled.")
		}

		//Create window
		global_window = SDL_CreateWindow("Space Invaders - Eshwary Mishra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (!global_window)
		{
			SI_LOG("Window could not be created. SDL Error: " << SDL_GetError())

			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			global_renderer = SDL_CreateRenderer(global_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (!global_renderer)
			{
				SI_LOG("Renderer could not be created. SDL Error: " << SDL_GetError())

				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int image_flags = IMG_INIT_PNG;

				if (!(IMG_Init(image_flags) & image_flags))
				{
					SI_LOG("SDL_image could not be initialized. SDL_image Error: " << IMG_GetError())

					success = false;
				}
			}
		}
	}

	return success;
}

bool Main::LoadMedia()
{
	bool success = true;

	//Load background
	if (!background_texture.LoadFromFile("background_texture.png"))
	{
		SI_LOG("Failed to load the player texture.")

		success = false;
	}

	//Load heart texture
	if (!heart_texture.LoadFromFile("heart_texture.png"))
	{
		SI_LOG("Failed to load the player texture.")

		success = false;
	}

	//Load player texture
	if (!player_texture.LoadFromFile("player_texture.png"))
	{
		SI_LOG("Failed to load the player texture.")

		success = false;
	}

	//Load basic enemy texture
	if (!enemy_basic_texture.LoadFromFile("enemy_basic_texture.png"))
	{
		SI_LOG("Failed to load the basic enemy texture.")

		success = false;
	}

	//Load intermediate enemy texture
	if (!enemy_intermediate_texture.LoadFromFile("enemy_intermediate_texture.png"))
	{
		SI_LOG("Failed to load the intermediate enemy texture.")

		success = false;
	}

	//Load advanced texture texture
	if (!enemy_advanced_texture.LoadFromFile("enemy_advanced_texture.png"))
	{
		SI_LOG("Failed to load the advanced enemy texture.")

		success = false;
	}

	//Load bomber enemy texture
	if (!enemy_bomber_texture.LoadFromFile("enemy_bomber_texture.png"))
	{
		SI_LOG("Failed to load the bomber enemy texture.")

		success = false;
	}

	//Load projectile bullet texture
	if (!projectile_bullet_texture.LoadFromFile("projectile_bullet_texture.png"))
	{
		SI_LOG("Failed to load the bomber enemy texture.")

		success = false;
	}

	return success;
}

void Main::Close()
{
	//Free loaded images
	background_texture.Free();
	heart_texture.Free();
	player_texture.Free();
	enemy_basic_texture.Free();
	enemy_intermediate_texture.Free();
	enemy_advanced_texture.Free();
	enemy_bomber_texture.Free();
	projectile_bullet_texture.Free();

	//Destroy window	
	SDL_DestroyRenderer(global_renderer);
	SDL_DestroyWindow(global_window);
	global_window = NULL;
	global_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void Main::AddEntity(std::shared_ptr<class SIObject> object)
{
	global_entities.push_back(object);
}

void Main::RemoveEntity(std::shared_ptr<class SIObject> object)
{
	global_entities.erase(std::remove(global_entities.begin(), global_entities.end(), object), global_entities.end());
}


bool Main::CheckCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the A boxes
	for (int Abox = 0; Abox < a.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		//Go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//A collision is detected
				return true;
			}
		}
	}

	//If neither set of collision boxes touched
	return false;
}

bool Main::CheckSimpleCollision(const SDL_Rect* a, const SDL_Rect* b)
{
	return SDL_HasIntersection(a, b);
}

SIObject* Main::CheckGlobalCollision(const SDL_Rect* a)
{
	SIObject* final = nullptr;

	for (int i = 0; i < global_entities.size(); i++)
	{
		std::shared_ptr<class SIObject> other = global_entities[i];

		if (a != other->GetSimpleCollider() && SDL_HasIntersection(a, other->GetSimpleCollider()))
		{
			final = other.get();

			break;
		}
	}

	return final;
}


int WinMain(int argc, char* argv[])
{
#if _DEBUG
	InitializeLogFile();
#endif

	//Start the main game
	Main main_app;

	//Start up SDL and create window
	if (!Main::GetInstance()->InitializeSDL())
	{
		SI_LOG("Failed to initialze.")
	}
	else
	{
		//Load media
		if (!Main::GetInstance()->LoadMedia())
		{
			SI_LOG("Failed to load media.")
		}
		else
		{
			Main::GetInstance()->MainTick();
		}
	}

	//Free resources and close SDL
	Main::GetInstance()->Close();

	return 0;
}