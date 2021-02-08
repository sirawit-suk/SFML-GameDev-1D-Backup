#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition, int mode)
	:animation(texture, imageCount)
{	
	this->mode = mode;
	this->speed = speed;
	this->switchTime = switchTime;

	body.setSize(Vector2f(160.f * 3, 160.f * 3));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setPosition(setPosition);
	body.setTexture(texture);

	hitbox.setSize(Vector2f(5.f * 3, 38.f * 3));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(body.getPosition().x, body.getPosition().y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(1.f);

	hpbar.setFillColor(Color(255,0,0,200));
	hpbar.setSize(Vector2f(hp, 7));

	hpbarbox.setSize(Vector2f(hp, 7));
	hpbarbox.setFillColor(Color(0, 0, 0, 150));
	hpbarbox.setOutlineColor(Color(0,0,0,150));
	hpbarbox.setOutlineThickness(2);


	armor = 0;
	if (mode == 1) {
		armor = 80;

		armorbar.setFillColor(Color(0, 255, 255,200));
		armorbar.setSize(Vector2f(armor, 7));

		armorbarbox.setSize(Vector2f(armor, 7));
		armorbarbox.setFillColor(Color(0, 0, 0, 150));
		armorbarbox.setOutlineColor(Color(0, 0, 0, 150));
		armorbarbox.setOutlineThickness(2);
	}
}

Enemy::~Enemy()
{
}

void Enemy::EnemyInput(const float& deltaTime, Vector2f gotoPosition)
{
	velocity.x = 0;
	velocity.y = 0;

	if (counterRandom >= 1.f)
	{ 
		random = rand() % 200; 
		counterRandom = 0.f;
		this->gotoPosition = gotoPosition;
	}
	counterRandom += deltaTime;

	if (gotoPosition.x - hitbox.getPosition().x >= 300 && random >= 0 && random < 40) { //go Right
		velocity.x += speed;
	}
	if (gotoPosition.x - hitbox.getPosition().x < 300 && random >= 40 && random < 80) { //go Left
		velocity.x -= speed;
	}
	if (random >= 80 && random < 90) { velocity.y -= speed; }
	if (random >= 90 && random < 100) { velocity.y += speed; }
	if (random >= 100 && random < 150) { }

	//Bullets
	if (bulletCount < bulletRate) { bulletCount++; isPush = false; }
	if (random >= 150 && random < 200 && bulletCount >= bulletRate && isShot == false)
	{
		isShot = true;
		isPush = true;
		soundeffect_shoot.play();
		bulletCount = 0;

	}
	else if (!(random >= 150 && random <= 200))
	{
		isShot = false;
		isPush = false;
	}
	
}

void Enemy::Update(const float& deltaTime)
{
	switchTime = 0.1;

	hpbar.setSize(Vector2f(hp, 7));
	if (armor <= 0) {
		armor = 0;
	}
	armorbar.setSize(Vector2f(armor, 7));


	/////////////////////////////////////////////// Animation //////////////////////////////////////////////////

	//Animations
	if (isAlive == true) {
		if (velocity.x == 0.f && velocity.y == 0.f)
		{
			//Stop walk
			row = 0;
			if (random >= 150 && random < 200) //shoot gun
			{

				if (gotoPosition.y - hitbox.getPosition().y > -100) { row = 2; }
				else if (gotoPosition.y - hitbox.getPosition().y <= -100) { row = 3; }
				switchTime = 0.35;
			}
			if (gotoPosition.x - hitbox.getPosition().x > 0) { faceRight = true; }
			else if (gotoPosition.x - hitbox.getPosition().x < 0) { faceRight = false; }
		}
		else
		{
			//Walking
			row = 1;
			if (random >= 150 && random < 200) //shoot gun
			{
				velocity.x = 0.f;
				velocity.y = 0.f;

				if (gotoPosition.y - hitbox.getPosition().y > -100) { row = 2; }
				else if (gotoPosition.y - hitbox.getPosition().y <= -100) { row = 3; }

				if (gotoPosition.x - hitbox.getPosition().x > 0) { faceRight = true; }
				else if (gotoPosition.x - hitbox.getPosition().x < 0) { faceRight = false; }
				switchTime = 0.35;
			}
			else
			{
				if (velocity.x > 0) { faceRight = true; }
				else if (velocity.x < 0) { faceRight = false; }
			}
		}

		animation.Update(row, deltaTime, faceRight, switchTime);
	}
	else {
		velocity.x = 0.f;
		velocity.y = 0.f;
		counterDead += deltaTime;
		if (counterDead <= switchTimeDead * 1.5) {
			randomdead = rand() % 3 + 5;
		}
		if (counterDead <= switchTimeDead * 1.5) {
			row = 4;
		}
		else if (counterDead <= switchTimeDead * 3) {
			row = randomdead;
		}
		if (counterDead >= switchTimeDead * 6) {
			UpdateChangeColorDead(deltaTime);
		}
		if (counterDead >= switchTimeDead * 14) {
			SetDeletePosition();
		}

		animation.Update(row, deltaTime, faceRight, switchTimeDead);
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	body.setTextureRect(animation.xyRect);

	hitbox.move(velocity * deltaTime);
	if (faceRight == true) { body.setPosition(hitbox.getPosition().x+20, hitbox.getPosition().y - 30); }
	else if (faceRight == false) { body.setPosition(hitbox.getPosition().x-20, hitbox.getPosition().y - 30); }
	
	hpbar.setPosition(hitbox.getPosition().x-50, hitbox.getPosition().y-70);
	hpbarbox.setPosition(hitbox.getPosition().x - 50, hitbox.getPosition().y - 70);

	if (mode == 1) {
		armorbar.setPosition(hitbox.getPosition().x - 50, hitbox.getPosition().y - 78);
		armorbarbox.setPosition(hitbox.getPosition().x - 50, hitbox.getPosition().y - 78);
	}

	if (isDamage == true) {
		UpdateChangeColor(deltaTime);
	}

}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);
	if (isAlive == true) {
		target.draw(hpbarbox);
		target.draw(hpbar);
		if (mode == 1) {
			target.draw(armorbarbox);
			target.draw(armorbar);
		}
	}



}




