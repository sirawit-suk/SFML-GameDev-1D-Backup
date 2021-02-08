#include "Plane.h"

Plane::Plane(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount1, Vector2u imageCount2, Vector2u imageCount3, float switchTime, float speed, Vector2f setPosition, int mode)
	:animation(texture, imageCount1), animationbomb(bombtexture, imageCount2), animationfire(firetexture, imageCount3)
{

	this->speed = speed;
	this->switchTime = switchTime;
	this->mode = mode;



	isRange = false;

	body.setSize(Vector2f(223, 95));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setPosition(setPosition);
	body.setTexture(texture);

	hp = 200;

	if (mode == 0) {
		hpbar.setFillColor(Color(255, 0, 0, 240));
		hpbar.setSize(Vector2f(hp, 12));

		hpbarbox.setSize(Vector2f(hp, 12));
		hpbarbox.setFillColor(Color::Transparent);
		hpbarbox.setOutlineColor(Color(0, 0, 0, 150));
		hpbarbox.setOutlineThickness(2);
	}
	
	if (mode == 2 || mode == 3) {
		body.setSize(Vector2f(300/2, 200/2));
		body.setFillColor(Color(100,100,100,255));
	}
	if (mode == 3) {
		faceRight = false;
	}


	bombeffect1.setSize(Vector2f(90 * 4, 90 * 4));
	bombeffect1.setOrigin(bombeffect1.getSize().x / 2.f, bombeffect1.getSize().y / 2.f);
	bombeffect1.setPosition(setPosition);
	bombeffect1.setTexture(bombtexture);

	hitbox.setSize(Vector2f(body.getSize()));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(body.getPosition().x, body.getPosition().y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(1.f);

	fireeffect.setSize(Vector2f(90 * 4, 90 * 4));
	fireeffect.setOrigin(fireeffect.getSize().x / 2.f, fireeffect.getSize().y / 2.f);
	fireeffect.setFillColor(Color(255, 255, 255, 230));
	fireeffect.setPosition(setPosition);
	fireeffect.setTexture(firetexture);

	fireeffect2.setSize(Vector2f(90 * 2, 90 * 2));
	fireeffect2.setOrigin(fireeffect2.getSize().x / 2.f, fireeffect2.getSize().y / 2.f);
	fireeffect2.setFillColor(Color(255, 255, 255, 245));
	fireeffect2.setPosition(setPosition);
	fireeffect2.setTexture(firetexture);

	fireeffect3.setSize(Vector2f(90 * 3, 90 * 3));
	fireeffect3.setOrigin(fireeffect3.getSize().x / 2.f, fireeffect3.getSize().y / 2.f);
	fireeffect3.setFillColor(Color(255, 255, 255, 240));
	fireeffect3.setPosition(setPosition);
	fireeffect3.setTexture(firetexture);

}

Plane::~Plane()
{
}

void Plane::Update(const float& deltaTime)
{
	if (mode==0) {
		if (hp <= 0) {
			hp = 0;
		}
		hpbar.setSize(Vector2f(hp, 12));
	}

	row = 0;

	if (mode == 3) {
		velocity.x = -speed; //Enemy
		if (hitbox.getPosition().x < -500) {
			hitbox.setPosition(13000, hitbox.getPosition().y);
		}
	}
	else if (mode == 2) {
		velocity.x = speed;	//Ally
		if (hitbox.getPosition().x > 13000) {
			hitbox.setPosition(-500, hitbox.getPosition().y);
		}
	}
	else if (mode == 0) {
		velocity.x = -speed; //Enemy
		if (hitbox.getPosition().x < -500) {
			SetDeletePosition();
		}
	}
	else if (mode == 1) {
		velocity.x = speed;	//Ally
		if (hitbox.getPosition().x > 13000) {
			SetDeletePosition();
		}
	}

	animation.Update(row, deltaTime, faceRight, switchTime);
	body.setTextureRect(animation.xyRect);

	hitbox.move(velocity * deltaTime);
	body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
	if (mode == 2) {
		body.setPosition(hitbox.getPosition().x+80, hitbox.getPosition().y+30);
	}

	if (mode == 0) {
		hpbar.setPosition(hitbox.getPosition().x-100, hitbox.getPosition().y-65);
		hpbarbox.setPosition(hitbox.getPosition().x-100, hitbox.getPosition().y-65);
	}

	if (isDamage == true) {
		UpdateChangeColor(deltaTime);
	}

	if (isAlive == false) {
		animationbomb.Update(0, deltaTime, faceRight, switchTime);
		bombeffect1.setTextureRect(animationbomb.xyRect);
		if (isAlreadySet == false) {
			bombeffect1.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);
			isAlreadySet = true;
		}

		animationfire.Update(0, deltaTime, faceRight, 0.3);
		fireeffect.setTextureRect(animationfire.xyRect);
		fireeffect.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);

		animationfire.Update(0, deltaTime, faceRight, 0.2);
		fireeffect2.setTextureRect(animationfire.xyRect);
		fireeffect2.setPosition(hitbox.getPosition().x - 50, hitbox.getPosition().y);

		animationfire.Update(0, deltaTime, faceRight, 0.2);
		fireeffect3.setTextureRect(animationfire.xyRect);
		fireeffect3.setPosition(hitbox.getPosition().x + 50, hitbox.getPosition().y - 50);

	}

}

void Plane::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);

	if (isAlive == true) {
		target.draw(hpbar);
		target.draw(hpbarbox);
	}
	else
	{
		if (animationbomb.isAnimationDoneTank() == false) {
			target.draw(bombeffect1);
		}
		target.draw(fireeffect);
		target.draw(fireeffect2);
		target.draw(fireeffect3);
	}

}
