#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

class Item
{
public:
	
	//Constructor/Destructor
	Item(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition, int mode);
	~Item();

	//Functions
	void UpdateChangeColorDead(const float& deltaTime);
	void SetDeletePosition();

	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	//Return Functions
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }

	bool isCollect;
	bool isStop;

private:

	int mode;

	Text gun;


	//Times
	float transparentDead;

	//Variables

	float randomstop;
	float totalTime;
	float totalTimeAnimation;
	float totalTimeDelete;

	float switchTimeAnimation;
	float switchTimeDead;


	float dtanimation;

	Animation animation;

	unsigned int row;
	float speed;
	float switchTime;

	//Speed
	Vector2f velocity;

	RectangleShape hitbox;
	RectangleShape body;

	//Deletes
	Vector2f OutscreenPosition;


};

