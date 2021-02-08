#pragma once
#include "Bullet.h"

class BulletBot : public Bullet
{
public:
	//Constructor/Destructor
	BulletBot(Texture* texture, Vector2f currPosition, Vector2f shootPosition, bool faceRight, int mode);
	~BulletBot();

	//Functions
	void Initial();
	void Move(float deltaTime);
	void Draw(RenderTarget& target);

private:

	//Variables
};
