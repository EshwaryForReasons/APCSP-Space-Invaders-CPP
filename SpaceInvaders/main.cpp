//Copyright Eshwary Mishra 2022

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "main.h"
#include "player.h"

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
}

Main::~Main()
{
	global_main = nullptr;
}

Main* Main::GetInstance()
{
	return global_main;
}


/**Starts up SDL and created window*/
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

/**Loads media*/
bool Main::LoadMedia()
{
	bool success = true;

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

	return success;
}

/**Frees media and shuts down SDL*/
void Main::Close()
{
	//Free loaded images
	player_texture.Free();
	enemy_basic_texture.Free();
	enemy_intermediate_texture.Free();
	enemy_advanced_texture.Free();
	enemy_bomber_texture.Free();

	//Destroy window	
	SDL_DestroyRenderer(global_renderer);
	SDL_DestroyWindow(global_window);
	global_window = NULL;
	global_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/**Box set collision detector*/
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
			bool quit = false;

			//Event handler
			SDL_Event event;

			//The player that will be moving around on the screen
			APlayer player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, &Main::GetInstance()->player_texture);

			//The collision test dot
			APlayer ctp(SCREEN_WIDTH / 4, SCREEN_HEIGHT - 400, &Main::GetInstance()->player_texture);

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
					player.HandleInput(event);
				}

				//Move the dot and check collision
				player.MovePlayer(ctp.GetColliders());

				//Clear screen
				SDL_SetRenderDrawColor(Main::GetInstance()->global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Main::GetInstance()->global_renderer);

				//Render dots
				player.Render();
				ctp.Render();

				//Update screen
				SDL_RenderPresent(Main::GetInstance()->global_renderer);
			}
		}
	}

	//Free resources and close SDL
	Main::GetInstance()->Close();

	return 0;
}