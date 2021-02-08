#pragma once
#include "Vehicle.h"

class Plane : public Vehicle
{
public:
	
	//Constructor/Destructor
	Plane(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount1, Vector2u imageCount2, Vector2u imageCount3, float switchTime, float speed, Vector2f setPosition, int mode);
	~Plane();

	//Functions
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	bool isRange;
	bool isAlreadyplay = false;

private:


	bool isAlreadySet =false;
	//Variables
	Animation animation;
	Animation animationbomb;
	Animation animationfire;
};

