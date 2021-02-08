#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace std;
using namespace sf;

class Bomb
{
public:

	//Constructors/Destuctors
	Bomb(Texture* texture, Vector2u imageCount, float switchTime, float speed, bool faceRight, Vector2f setPosition, int mode);
	~Bomb();

	//Functions
	void SetDeletePosition();
	
	void UpdateChangeColorDead(const float& deltaTime);
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	//Return Functions
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	FloatRect GetGlobalbounce() { return areabox.getGlobalBounds(); }

	bool isAlreadyBoom;
	bool isBoom;
	bool isHit;

private:



	//Times
	float transparentDead;

	float totalTime;
	float totalDeadTime;

	Animation animation;
	int row;

	bool faceRight;

	//Variables
	int mode;

	float speed;
	float switchTime;

	RectangleShape body;
	RectangleShape hitbox;
	RectangleShape areabox;

	Vector2f OutscreenPosition;

};

