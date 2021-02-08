#include "Platform.h"

Platform::Platform(Texture* texture, Vector2f size, Vector2u imageCount, bool faceRight, Vector2f position, int mode)
	:animation(texture, imageCount)
{
	this->faceRight = faceRight;
	this->imageCount = imageCount;
	this->mode = mode;
	row = 0;
	if (mode == 0)
	{
		hitbox.setSize(size);
		hitbox.setOrigin(size / 2.f);
		hitbox.setPosition(position);
		hitbox.setFillColor(Color::Transparent);
		hitbox.setOutlineColor(Color::Red);
		hitbox.setOutlineThickness(2);

		body.setFillColor(Color::Transparent);
	}
	else
	{

		if (mode == 1)
		{
			row = 0;
			body.setSize(Vector2f(180.f*3,180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox.setSize(Vector2f(150, 1.f));		//Long Left
			hitbox.setOrigin(hitbox.getSize() / 2.f);
			hitbox.setPosition(position.x-80,position.y-55);
			hitbox.setFillColor(Color::Transparent);
			hitbox.setOutlineColor(Color::Red);
			hitbox.setOutlineThickness(2);

			hitbox2.setSize(Vector2f(200, 1.f));	//Long below
			hitbox2.setOrigin(hitbox2.getSize() / 2.f);
			hitbox2.setPosition(position.x+80, position.y - 45);
			hitbox2.setFillColor(Color::Transparent);
			hitbox2.setOutlineColor(Color::Red);
			hitbox2.setOutlineThickness(2);
		}
		else if (mode == 2)	//CAN'T WALK THROUGH
		{
			row = 1;
			body.setSize(Vector2f(180.f * 3, 180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox.setSize(Vector2f(180, 20.f));			//BIG CAN'T WALK
			hitbox.setOrigin(hitbox.getSize() / 2.f);
			hitbox.setPosition(position.x+40, position.y-20);
			hitbox.setFillColor(Color::Transparent);
			hitbox.setOutlineColor(Color::Red);
			hitbox.setOutlineThickness(2);

			hitbox2.setSize(Vector2f(200, 20.f));			//LONG TOP
			hitbox2.setOrigin(hitbox2.getSize() / 2.f);
			hitbox2.setPosition(position.x-60, position.y-55);
			hitbox2.setFillColor(Color::Transparent);
			hitbox2.setOutlineColor(Color::Red);
			hitbox2.setOutlineThickness(2);

		}
		else if (mode == 3)
		{
			row = 2;
			body.setSize(Vector2f(180.f * 3, 180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox2.setSize(Vector2f(80, 20.f));			//LONG TOP
			hitbox2.setOrigin(hitbox2.getSize() / 2.f);
			hitbox2.setPosition(position.x, position.y - 45);
			hitbox2.setFillColor(Color::Transparent);
			hitbox2.setOutlineColor(Color::Red);
			hitbox2.setOutlineThickness(2);

		}
		else if (mode == 4)
		{
			row = 3;
			body.setSize(Vector2f(180.f * 3, 180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox.setSize(Vector2f(80, 20.f));			//LONG TOP
			hitbox.setOrigin(hitbox.getSize() / 2.f);
			hitbox.setPosition(position.x, position.y - 35);
			hitbox.setFillColor(Color::Transparent);
			hitbox.setOutlineColor(Color::Red);
			hitbox.setOutlineThickness(2);
		}
		else if (mode == 5)
		{
			row = 4;
			body.setSize(Vector2f(180.f * 3, 180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox.setSize(Vector2f(80, 20.f));			//LONG TOP
			hitbox.setOrigin(hitbox.getSize() / 2.f);
			hitbox.setPosition(position.x, position.y - 35);
			hitbox.setFillColor(Color::Transparent);
			hitbox.setOutlineColor(Color::Red);
			hitbox.setOutlineThickness(2);
		}
		else if (mode == 6)
		{
			row = 5;
			body.setSize(Vector2f(180.f * 3, 180.f * 3));
			body.setOrigin(body.getSize() / 2.f);
			body.setTexture(texture);
			body.setPosition(position);

			hitbox.setSize(Vector2f(345, 20.f));			//LONG TOP
			hitbox.setOrigin(hitbox.getSize() / 2.f);
			hitbox.setPosition(position.x, position.y - 35);
			hitbox.setFillColor(Color::Transparent);
			hitbox.setOutlineColor(Color::Red);
			hitbox.setOutlineThickness(2);
		}
	}
	
	animation.Update(row, 0, faceRight, 0);
	body.setTextureRect(animation.xyRect);
}

Platform::~Platform()
{
}

void Platform::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);
	//target.draw(hitbox2);
}
