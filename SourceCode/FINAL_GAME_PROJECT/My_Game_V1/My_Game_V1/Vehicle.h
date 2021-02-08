#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace sf;
using namespace std;

class Vehicle
{
public:

	//Constructor/Destructor
	Vehicle();
	~Vehicle();

	void UpdateChangeColor(const float& deltaTime);
	void UpdateChangeColorDead(const float& deltaTime);
	void SetDeletePosition();
	void SetPosition(int x,int y);
	void SetPosition5800();
	void SetPosition9000();

	//Functions
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	
	bool isAlive;
	bool isPush;
	bool isDamage;
	int hp;

	Vector2f velocity;

protected:

	bool isFire;
	//Variables for Vehicles
	int mode;

	int random;
	int randomdead;

	//Body
	RectangleShape areabox;

	RectangleShape hitbox;
	RectangleShape body;

	RectangleShape bombeffect1;
	RectangleShape fireeffect;
	RectangleShape fireeffect2;
	RectangleShape fireeffect3;

	Vector2f gotoPosition;

	//Health bar
	RectangleShape hpbar;
	RectangleShape hpbarbox;

	//Times
	float transparentDead;

	float counterRandom;
	float counterBlink;
	float counterDead;
	float totalTime;

	float switchTime;
	float switchTimeDead;

	//Animations
	unsigned int row;
	float speed;
	bool faceRight;

	//Speed
	Vector2f setPositionTemp;

	//Bullets
	bool isShot;
	unsigned int bulletRate;
	unsigned int bulletCount;
	Vector2f bulletVelocity;

	//Deletes
	Vector2f OutscreenPosition;


};

