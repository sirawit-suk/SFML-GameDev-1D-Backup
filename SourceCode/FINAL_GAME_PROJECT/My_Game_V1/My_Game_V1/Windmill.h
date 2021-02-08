#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace std;
using namespace sf;

class Windmill
{
public:
	//Constructor/Destructor
	Windmill(Texture* texture, Texture* wing, Texture* flag, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition);
	~Windmill();

	//Functions

	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	//Return Functions
	Vector2f GetPosition() { return basebody.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	FloatRect GetGlobalbounce() { return hitbox.getGlobalBounds(); }
	bool GetComplete() { return isComplete; }

	float flagTotal;
	float flagRed;
	float flagBlue;

	bool isActiveAlly;
	bool isActiveEnemy;

	bool isComplete;

private:

	float totalTime;

	//Variables
	RectangleShape flagbar;
	RectangleShape flagbarbox;

	Animation animation;

	unsigned int row;
	float speed;
	float switchTime;

	//Speed
	Vector2f velocity;

	RectangleShape hitbox;
	RectangleShape wingbody;
	RectangleShape basebody;

	RectangleShape flagbody;
	RectangleShape pole;

	float angle = 0;
};

