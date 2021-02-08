#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Collision
{
public:

	//Constructor/Destructor
	Collision(RectangleShape& body);
	~Collision();

	//Functions
	void Move(float dx, float dy) { body.move(dx,dy); }

	//Variables
	bool CheckCollision(Collision other, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.f; }

private:

	//Variables
	RectangleShape& body;
};

