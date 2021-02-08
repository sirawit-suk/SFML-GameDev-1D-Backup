#include "BulletPlayer.h"

BulletPlayer::BulletPlayer(Texture* texture, Vector2f currPosition, Vector2f aimDirNorm, Vector2f aimDir, bool faceRight)
	
{
	this->faceRight = faceRight;
	this->currPosition = currPosition;
	this->aimDir = aimDir;
	this->aimDirNorm = aimDirNorm;

	bulletShape.setFillColor(Color::Yellow);
	bulletShape.setTexture(texture);

	hitbox.setPosition(currPosition.x, currPosition.y);
	Initial(); 
}

BulletPlayer::~BulletPlayer()
{
}

void BulletPlayer::Initial()
{
	// set Position //

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
	//cout << currVelocity.x << "  " << currVelocity.y << endl;	
}

void BulletPlayer::Move(float deltaTime)
{
	hitbox.move(currVelocity * deltaTime);
	bulletShape.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
}

void BulletPlayer::Draw(RenderTarget& target)
{
	target.draw(bulletShape);
	//target.draw(hitbox);
}


