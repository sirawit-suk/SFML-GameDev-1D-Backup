#pragma once
#include "Bullet.h"

class BulletPlayer : public Bullet
{
public:
	//Constructor/Destructor
	BulletPlayer(Texture* texture, Vector2f currPosition, Vector2f aimDirNorm, Vector2f aimDir, bool faceRight);
	~BulletPlayer();

	//Functions
	void Initial();
	void Move(float deltaTime);
	void Draw(RenderTarget& target);

private:

	//Variables

};

