//Copyright Eshwary Mishra 2022

#pragma once

#include <string>

#include <SDL.h>

enum class EFontSize
{
	FS_TITLE,
	FS_NORMAL,
	FS_SMALL
};

class UTexture
{
public:
	//Initializes variables
	UTexture();

	//Deallocates memory
	~UTexture();


	/**Loads image at specified path*/
	bool LoadFromFile(std::string path);

	/**Creates image from font string*/
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor, const EFontSize& font_size);

	/**Deallocates texture*/
	void Free();


	/**Set color modulation*/
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	/**Set blending*/
	void SetBlendMode(SDL_BlendMode blending);

	/**Set alpha modulation*/
	void SetAlpha(Uint8 alpha);


	/**Renders texture at given point*/
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	/**Returns the image width*/
	int GetWidth() {return width;};

	/**Returns the image height*/
	int GetHeight() {return height;};

private:

	//The actual hardware texture
	SDL_Texture* main_texture;

	//Image dimensions
	int width;
	int height;
};

