#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collision.h"

using namespace sf;
using namespace std;

class Bullet
{
public:

	//Constructor/Destructor
	Bullet();
	~Bullet();

	//Functions
	void SetDeletePosition();

	Vector2f GetPosition() { return bulletShape.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }

protected:

	//Variables

	CircleShape bulletShape;
	RectangleShape hitbox;

	Vector2f currVelocity;
	Vector2f currPosition;
	Vector2f shootPosition;

	Vector2f aimDir;
	Vector2f aimDirNorm;

	bool faceRight;
	float maxSpeed;

	int mode;

	//Deletes
	Vector2f OutscreenPosition;



};

