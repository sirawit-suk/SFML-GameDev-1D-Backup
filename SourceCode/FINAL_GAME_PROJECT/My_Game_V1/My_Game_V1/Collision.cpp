#include "Collision.h"

Collision::Collision(RectangleShape& body)
	:body(body)
{

}

Collision::~Collision()
{
}

bool Collision::CheckCollision(Collision other, float push)
{
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		push = min(max(push, 0.f), 1.f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.f)
			{
				Move(intersectX * (1.f - push), 0.f);
				other.Move(-intersectX * push, 0.f);
			}
			else
			{
				Move(-intersectX * (1.f - push), 0.f);
				other.Move(intersectX * push, 0.f);
			}
		}
		else
		{
			if (deltaY > 0.f)
			{
				Move(0.f, intersectY * (1.f - push));
				other.Move(0.f, -intersectY * push);
			}
			else
			{
				Move(0.f, -intersectY * (1.f - push));
				other.Move(0.f, intersectY * push);
			}
		}
		
		return true;
	}



	return false;
}
