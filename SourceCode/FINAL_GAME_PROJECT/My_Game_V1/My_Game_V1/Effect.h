#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace std;
using namespace sf;

class Effect
{
public:
	
	//Constuctor/Destructor
	Effect(Texture* texture, Vector2u imageCount, float switchTime, float speed, bool faceRight, Vector2f setPosition, int mode);
	~Effect();

	//Functions
	void UpdateChangeColorDead(const float& deltaTime);
	void SetDeletePosition();

	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	//Return Functions
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	FloatRect GetGlobalbounce() { return hitbox.getGlobalBounds(); }

	bool isBomb;
	int randomstop = 0;
	bool isMissionbomb = false;

private:

	bool isStop;


	//Times
	float transparentDead;

	float totalTime;
	float totalTimeAnimation;

	Animation animation;
	int row;

	bool faceRight;

	//Variables
	int mode;

	float speed;
	float switchTime;

	RectangleShape body;
	RectangleShape hitbox;

	Vector2f velocity;

	Vector2f OutscreenPosition;

};

