#pragma once
#include "Human.h"

class Enemy : public Human
{
public:

	//Constructor/Destructor
	Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition, int mode);
	~Enemy();

	//Functions
	void EnemyInput(const float& deltaTime, Vector2f gotoPosition);
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	int GetMode() { return mode; }

private:

	//Variables
	Animation animation;

	int mode;

};

