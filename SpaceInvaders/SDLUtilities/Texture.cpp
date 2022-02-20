//Copyright Eshwary Mishra 2022

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "main.h"
#include "Texture.h"

UTexture::UTexture()
{
	main_texture = NULL;
	width = 0;
	height = 0;
}

UTexture::~UTexture()
{
	Free();
}


bool UTexture::LoadFromFile(std::string path)
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (!loadedSurface)
	{
		SI_LOG("Uanable to load image " << path.c_str() << ". SDL_image Error: " << IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Main::GetInstance()->global_renderer, loadedSurface);

		if (!newTexture)
		{
			SI_LOG("Uanable to create texture from " << path.c_str() << ". SDL Error: " << SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	main_texture = newTexture;
	return main_texture != NULL;
}

bool UTexture::LoadFromRenderedText(std::string textureText, SDL_Color textColor, const EFontSize& font_size)
{
	//Get rid of preexisting texture
	Free();

	TTF_Font* font = nullptr;

	switch (font_size)
	{
	case EFontSize::FS_TITLE:
		font = Main::GetInstance()->global_font_title;
		break;
	case EFontSize::FS_NORMAL:
		font = Main::GetInstance()->global_font_normal;
		break;
	case EFontSize::FS_SMALL:
		font = Main::GetInstance()->global_font_small;
		break;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

	if (textSurface == NULL)
	{
		SI_LOG("Unable to render text surface: " << textureText.c_str() << ". SDL_ttf Error: " << TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		main_texture = SDL_CreateTextureFromSurface(Main::GetInstance()->global_renderer, textSurface);

		if (main_texture == NULL)
		{
			SI_LOG("Uanable to create texture from rendered text: SDL Error: " << SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return main_texture != NULL;
}


void UTexture::Free()
{
	//Free texture if it exists
	if (main_texture != NULL)
	{
		SDL_DestroyTexture(main_texture);
		main_texture = NULL;
		width = 0;
		height = 0;
	}
}

void UTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(main_texture, red, green, blue);
}

void UTexture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(main_texture, blending);
}

void UTexture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(main_texture, alpha);
}

void UTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(Main::GetInstance()->global_renderer, main_texture, clip, &renderQuad, angle, center, flip);
}