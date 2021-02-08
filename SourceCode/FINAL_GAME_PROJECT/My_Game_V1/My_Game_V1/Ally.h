#pragma once
#include "Human.h"

class Ally : public Human
{
public:

	//Constructor/Destructor
	Ally(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition, int mode);
	~Ally();

	//Functions
	void AllyInput(const float& deltaTime, Vector2f gotoPosition);
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	bool isUpdate;

private:

	//Variables
	Animation animation;
	int mode;

};
