#pragma once
#include "Vehicle.h"
class Tank : public Vehicle
{
public:

	//Constructor/Destructor
	Tank(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount1, Vector2u imageCount2, Vector2u imageCount3, float switchTime, float speed, Vector2f setPosition, int mode);
	~Tank();

	//Functions
	void TankInput(const float& deltaTime, Vector2f gotoPosition);
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window
	void DrawUI(RenderTarget& target);

	FloatRect GetGlobalbounceisRange() { return areabox2.getGlobalBounds(); }
	FloatRect GetGlobalbounce() { return hitbox.getGlobalBounds(); }

	bool isRange;
	bool isAppearArea;

private:

	//Variables
	Animation animation;
	Animation animationbomb;
	Animation animationfire;

	RectangleShape areabox2;

	bool changeFade;
	float colorValue;

};

