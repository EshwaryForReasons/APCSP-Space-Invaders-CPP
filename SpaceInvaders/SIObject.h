//Copyright Eshwary Mishra 2022

#pragma once

#include <SDL.h>

class SIObject
{
public:

	SIObject(int x, int y, class UTexture* object_texture);

	/**Called every frame*/
	virtual void Tick();

	/**Returns the simple collision box*/
	SDL_Rect* GetSimpleCollider() {return &simple_collider;};

	/**Renders the object on the screen*/
	void Render();


	/**Take damage*/
	virtual void TakeDamage();

	/**The death logic*/
	virtual void Die();

	int object_width = 20;

	/**The Y offset of the object*/
	int y_position;

protected:

	int object_height = 20;

	/**The X offset of the object*/
	int x_position;

	/**The Y velocity of the object*/
	int x_velocity;

	/**The Y velocity of the object*/
	int y_velocity;


	/**The object's simple collider*/
	SDL_Rect simple_collider;

	/**The texture of the object*/
	class UTexture* object_texture;
};

