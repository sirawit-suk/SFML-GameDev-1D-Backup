#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collision.h"

using namespace std;
using namespace sf;

class Tower
{
public:
	Tower(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount2, Vector2u imageCount3, float switchTime, Vector2f setPosition, int mode);
	~Tower();

	//Functions
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	void UpdateChangeColor(const float& deltaTime);

	//Functions
	Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(hitbox); }
	FloatRect GetGlobalbounce() { return hitbox.getGlobalBounds(); }

	bool isAlive;
	bool isDamage;
	bool isAlreadyBoom;
	int hp;

	bool isStart;


private:
	

	int mode;
	int row;
	bool faceRight;

	Animation animationbomb;
	Animation animationfire;

	float switchTime;


	RectangleShape body;
	RectangleShape hitbox;

	RectangleShape bombeffect;
	RectangleShape fireeffect1;
	RectangleShape fireeffect2;
	
	RectangleShape hpbar;
	RectangleShape hpbarbox;

	float counterBlink;


};

