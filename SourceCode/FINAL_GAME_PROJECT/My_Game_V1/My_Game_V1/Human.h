#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace sf;
using namespace std;

class Human
{
public:

	//Constructor/Destructor
	Human();
	virtual ~Human();

	//Functions
	void UpdateChangeColor(const float& deltaTime);
	void UpdateChangeColorDead(const float& deltaTime);
	void SetDeletePosition();

	//Return function
	bool GetfaceRight() { return faceRight; };
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	FloatRect GetGlobalbounce() { return hitbox.getGlobalBounds(); }

	//Check state
	bool isAlive;
	bool isPush;
	bool isDamage;
	int hp;
	int armor;

protected:
	
	Font font;
	Text newgunText;
	Text outofammoText;
	Text hpplusText;

	//Variables for Human
	int random;
	int randomdead;

	//Body
	RectangleShape hitbox;
	RectangleShape body;

	Vector2f gotoPosition;

	//Health bar
	RectangleShape hpbar;
	RectangleShape hpbarbox;

	//Armor bar
	RectangleShape armorbar;
	RectangleShape armorbarbox;

	//Times
	float transparentDead;

	float totalTime;
	float counterRandom;
	float counterBlink;
	float counterDead;

	float switchTime;
	float switchTimeDead;

	//Animations
	unsigned int row;
	float speed;
	bool faceRight;

	//Speed
	Vector2f velocity;

	//Bullets
	bool isShot;
	unsigned int bulletRate;
	unsigned int bulletCount;
	Vector2f bulletVelocity;

	//Deletes
	Vector2f OutscreenPosition;
	
	//Sounds
	SoundBuffer sf_shoot;
	Sound soundeffect_shoot;

	SoundBuffer sf_walk;
	Sound soundeffect_walk;

};

