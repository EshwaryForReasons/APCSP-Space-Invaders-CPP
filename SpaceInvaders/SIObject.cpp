//Copyright Eshwary Mishra 2022

#include "SIObject.h"
#include "SDLUtilities/Texture.h"

SIObject::SIObject(int x, int y, UTexture* _object_texture)
{
	object_texture = _object_texture;

	//Initialize the offsets
	x_position = x;
	y_position = y;

	//Initialize the velocity
	x_velocity = 0;
	y_velocity = 0;

	simple_collider.x = x_position;
	simple_collider.y = y_position;
}

void SIObject::Tick()
{

}

void SIObject::Render()
{
	//Show the dot
	object_texture->Render(x_position, y_position);
}