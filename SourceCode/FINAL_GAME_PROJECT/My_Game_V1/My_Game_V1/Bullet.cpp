#include "Bullet.h"

Bullet::Bullet()
{
	bulletShape.setRadius(5.f);
	bulletShape.setOrigin(bulletShape.getRadius() / 2, bulletShape.getRadius() / 2);

	hitbox.setSize(Vector2f(bulletShape.getRadius(), bulletShape.getRadius()));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Green);
	hitbox.setOutlineThickness(1.f);

	this->maxSpeed = 1000.f;
	this->faceRight = true;

	this->mode = 0;

	this->currPosition = Vector2f(0,0);
	this->currVelocity = Vector2f(0,0);
	this->shootPosition = Vector2f(0,0);

	this->aimDir = Vector2f(0, 0);
	this->aimDirNorm = Vector2f(0, 0);

	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;
}

Bullet::~Bullet()
{
}

void Bullet::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}