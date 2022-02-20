//Copyright Eshwary Mishra 2022

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "SDLUtilities/Texture.h"

#ifdef _DEBUG
#ifndef SI_LOG
static std::ofstream myfile;
#define SI_LOG(LogInfo) myfile.open("log.txt", std::fstream::app); myfile << LogInfo << std::endl; myfile.close();
#endif

static void InitializeLogFile()
{
	time_t t = time(NULL);
	struct tm tPtr;
	localtime_s(&tPtr, &t);

	std::ostringstream new_log_file_name;
	new_log_file_name << "log_backup_" << tPtr.tm_mday << "." << (tPtr.tm_mon + 1) << "." << (tPtr.tm_year + 1900) << "_" << tPtr.tm_hour << "." << tPtr.tm_min << "." << tPtr.tm_sec << ".txt";

	std::string rename_command("rename log.txt \"" + new_log_file_name.str() + "\"");
	std::string move_command("move \"" + new_log_file_name.str() + "\" .\\BackupLogs");

	//Move old log file
	system(rename_command.c_str());
	system(move_command.c_str());

	//Create new log file
	system("type nul > log.txt");
}

#elif NDEBUG
#ifndef SI_LOG
#define SI_LOG(x)
#endif
#endif

void InsertNewError(std::string Error);


static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 600;

enum class EGameState
{
	GS_MainMenu,
	GS_MainGame,
	GS_GameOver
};

class Main
{
public:

	Main();
	~Main();

	static Main* GetInstance();


	/**The ticker object for main, responsible for all game logic*/
	void MainTick();


	/**The SDL window we will be rendering to*/
	SDL_Window* global_window;

	/**The window renderer*/
	SDL_Renderer* global_renderer;

	/**The font to use throughout the game*/
	TTF_Font* global_font_title;

	/**The font to use throughout the game*/
	TTF_Font* global_font_normal;

	/**The font to use throughout the game*/
	TTF_Font* global_font_small;


	/**SDL event handler*/
	SDL_Event event;


	/**The texture of the background*/
	UTexture background_texture;

	/**The texture of the space invaders logo*/
	UTexture space_invaders_logo_texture;

	/**The texture of the player*/
	UTexture heart_texture;

	/**The texture of the player*/
	UTexture player_texture;

	/**The texture of the player*/
	UTexture enemy_basic_texture;

	/**The texture of the player*/
	UTexture enemy_intermediate_texture;

	/**The texture of the player*/
	UTexture enemy_advanced_texture;

	/**The texture of the player*/
	UTexture enemy_bomber_texture;

	/**The texture of the bullet*/
	UTexture projectile_bullet_texture;


	/**The current game mode class*/
	class UGameModeBase* current_game_mode;


	/**List of all objects in the game*/
	std::vector<class SIObject*> global_entities;


	/**Should the game keep running*/
	bool quit = false;


	/**Changes the game mode*/
	void ChangeGameState(const EGameState& new_game_state);


	/**Returns list of all objects in the game*/
	std::vector<class SIObject*> GetGlobalEntities() {return global_entities;};

	/**Adds an entity to the list*/
	void AddEntity(class SIObject* object);

	/**Removes an entity from the list*/
	void RemoveEntity(class SIObject* object);


	/**Box set collision detector*/
	bool CheckCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

	/**Box set collision detector*/
	bool CheckSimpleCollision(const SDL_Rect *a, const SDL_Rect* b);

	/**Checks whether the given rect intersects with any other in the world*/
	class SIObject* CheckGlobalCollision(const SDL_Rect* a);


	/**Starts up SDL and created window*/
	bool InitializeSDL();

	/**Loads media*/
	bool LoadMedia();

	/**Frees media and shuts down SDL*/
	void Close();

private:

	/**The current game state*/
	EGameState current_game_state;
};