#include "BulletBot.h"

BulletBot::BulletBot(Texture* texture, Vector2f currPosition, Vector2f shootPosition, bool faceRight, int mode)
{
	this->mode = mode;
	this->maxSpeed = 800.f;
	this->currPosition = currPosition;
	this->shootPosition = shootPosition;
	this->faceRight = faceRight;

	if (mode == 0) {
		bulletShape.setFillColor(Color(255, 100, 0));//Yellow Red // Enemys
	}
	else if (mode == 1) {
		bulletShape.setFillColor(Color(0, 255, 0));//Green //Allys
	}
	else if (mode == 2) {
		bulletShape.setFillColor(Color(200, 80, 0));//Yellow Red // Enemys
	}
	else if (mode == 3) {
		bulletShape.setFillColor(Color(0, 170, 0));//Green //Allys
	}

	bulletShape.setTexture(texture);

	hitbox.setPosition(currPosition.x, currPosition.y);
	Initial();
}

BulletBot::~BulletBot()
{
}

void BulletBot::Initial()
{
	// set Position //
	aimDir = shootPosition - currPosition;
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

	if (aimDir.x >= 0) { faceRight = true; }
	else { faceRight = false; }

	if (faceRight == true) //RIGHT
	{
		if (aimDir.y > -100) { hitbox.setPosition(currPosition.x + 80, currPosition.y + 5); }//DOWN
		else if (aimDir.y <= -100) { hitbox.setPosition(currPosition.x + 60, currPosition.y - 45); }//UP
	}
	else if (faceRight == false) //LEFT
	{
		if (aimDir.y > -100) { hitbox.setPosition(currPosition.x - 80, currPosition.y + 5); }//DOWN
		else if (aimDir.y <= -100) { hitbox.setPosition(currPosition.x - 60, currPosition.y - 45); }//UP
	}

	// set Velocity and Direction //
	currVelocity = aimDirNorm * maxSpeed;

	if (currVelocity.y >= 500.f)	// DOWN
	{
		currVelocity.y = 500.f;
		if (faceRight == false) { if (currVelocity.x > -1800.f) { currVelocity.x = -1800.f; } }
		else if (faceRight == true) { if (currVelocity.x < 1800.f) { currVelocity.x = 1800.f; } }
	}
	if (currVelocity.y <= -1000.f)  // UP
	{
		currVelocity.y = -1000.f;
		if (faceRight == false) { if (currVelocity.x > -1700.f) { currVelocity.x = -1700.f; } }
		else if (faceRight == true) { if (currVelocity.x < 1700.f) { currVelocity.x = 1700.f; } }
	}
}

void BulletBot::Move(float deltaTime)
{
	hitbox.move(currVelocity * deltaTime);
	bulletShape.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
}

void BulletBot::Draw(RenderTarget& target)
{
	target.draw(bulletShape);
	//target.draw(hitbox);
}


