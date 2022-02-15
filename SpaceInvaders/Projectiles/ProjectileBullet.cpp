//Copyright Eshwary Mishra 2022

#include "ProjectileBullet.h"
#include "main.h"
#include "Pawn.h"

AProjectileBullet::AProjectileBullet(int x, int y, UTexture* _object_texture, APawn* _owner) : SIObject(x, y, _object_texture)
{
	object_width = 5;
	object_height = 10;

	simple_collider.w = object_width;
	simple_collider.h = object_height;

	x_velocity = 0;
	y_velocity = -5;

	owner = _owner;
}

void AProjectileBullet::Tick()
{
	SIObject::Tick();

	hit_item = (APawn*)(Main::GetInstance()->CheckGlobalCollision(&simple_collider));

	MoveProjectile();
}

void AProjectileBullet::MoveProjectile()
{
	//Move the dot left or right
	x_position += x_velocity;
	simple_collider.x = x_position;

	//If the dot collided or went too far to the left or right
	if ((x_position < 0) || (x_position + object_width > SCREEN_WIDTH) || (hit_item && hit_item != owner))
	{
		//Move back
		x_position -= x_velocity;
		simple_collider.x = x_position;

		OnHit();
	}

	//Move the dot up or down
	y_position += y_velocity;
	simple_collider.y = y_position;

	//If the dot collided or went too far up or down
	if ((y_position < 0) || (y_position + object_height > SCREEN_HEIGHT) || (hit_item && hit_item != owner))
	{
		//Move back
		y_position -= y_velocity;
		simple_collider.y = y_position;

		OnHit();
	}
}


void AProjectileBullet::OnHit()
{
	if (hit_item && hit_item != owner)
	{
		hit_item->TakeDamage();
	}

	for (std::shared_ptr<SIObject> object : Main::GetInstance()->GetGlobalEntities())
	{
		if (object.get() == this)
		{
			owner->bHasBullet = false;

			Main::GetInstance()->RemoveEntity(object);
		}
	}
}