#pragma once
#include <iostream>
#include "Collision.h"
#include "Animation.h"

using namespace std;
using namespace sf;

class Platform
{
public:

	//Constructor/Destructor
	Platform(Texture* texture, Vector2f size, Vector2u imageCount, bool faceRight, Vector2f position, int mode);
	~Platform();
	
	//Functions
	void Draw(RenderTarget& target);
	Collision GetCollision() { return Collision(hitbox); }
	Collision GetCollision2() { return Collision(hitbox2); }

private:

	int row;

	Vector2u imageCount;
	bool faceRight;

	//Variables
	int mode;
	RectangleShape body;
	RectangleShape hitbox;
	RectangleShape hitbox2;

	Animation animation;

};

