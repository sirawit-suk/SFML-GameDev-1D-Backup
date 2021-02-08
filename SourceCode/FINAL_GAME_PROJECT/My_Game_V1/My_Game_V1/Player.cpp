#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed)
	:animation(texture, imageCount)
{
	//UI Player 
	pf.loadFromFile("Resource/Picture/edward.jpg");
	profile.setPosition(20, 20);
	profile.setSize(Vector2f(200, 200));
	profile.setTexture(&pf);
	profile.setOutlineColor(Color::Black);
	profile.setOutlineThickness(3);

	gunbox.setPosition(240, 95);
	gunbox.setSize(Vector2f(200, 125));
	gunbox.setFillColor(Color(200,200,50,200));
	gunbox.setOutlineThickness(3);
	gunbox.setOutlineColor(Color::Black);

	sizegun = 180.f;

	g1.loadFromFile("Resource/Picture/garandgun.png");
	gun1.setSize(Vector2f(sizegun, sizegun));
	gun1.setOrigin(gun1.getSize().x/2 , gun1.getSize().y / 2);
	gun1.setPosition(gunbox.getPosition().x+gunbox.getSize().x / 2, gunbox.getPosition().y+gunbox.getSize().y / 2-10);
	gun1.setTexture(&g1);

	gunText1.setFont(font);
	gunText1.setString("M1 GARAND");
	gunText1.setFillColor(Color::Black);
	gunText1.setLetterSpacing(2);
	gunText1.setCharacterSize(20);
	gunText1.setPosition(gunbox.getGlobalBounds().left + 13 + gunbox.getSize().x / 10, gunbox.getGlobalBounds().top + gunbox.getSize().y / 1.3);

	g2.loadFromFile("Resource/Picture/thomsongun.png");
	gun2.setSize(Vector2f(sizegun, sizegun));
	gun2.setOrigin(gun2.getSize().x / 2, gun2.getSize().y / 2);
	gun2.setPosition(gunbox.getPosition().x + gunbox.getSize().x / 2, gunbox.getPosition().y + gunbox.getSize().y / 2-10);
	gun2.setTexture(&g2);

	gunText2.setFont(font);
	gunText2.setString("M1A1 THOMPSON");
	gunText2.setFillColor(Color::Black);
	gunText2.setLetterSpacing(2);
	gunText2.setCharacterSize(17);
	gunText2.setPosition(gunbox.getGlobalBounds().left + gunbox.getSize().x / 10, gunbox.getGlobalBounds().top + gunbox.getSize().y / 1.3);


	

	this->speed = speed;
	this->switchTime = switchTime;
	this->totalTime = 0;
	this->isNewgun = false;
	this->isOut = false;

	body.setSize(Vector2f(160.f*3, 160.f*3));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setPosition(1000.f,700); //580
	body.setTexture(texture);
	
	hitbox.setSize(Vector2f(5.f*3, 38.f*3));
	hitbox.setOrigin( (hitbox.getSize().x / 2.f) , (hitbox.getSize().y / 2.f));
	hitbox.setPosition(body.getPosition().x, body.getPosition().y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Green);
	hitbox.setOutlineThickness(1.f);

	hp = 800; //special
	hpbar.setFillColor(Color::Green);
	hpbar.setSize(Vector2f(hp,30));
	hpbar.setPosition(Vector2f(240,20));
	
	hpbarbox.setFillColor(Color(200, 200, 200, 100));
	hpbarbox.setOutlineColor(Color(0,0,0,200));
	hpbarbox.setOutlineThickness(2);
	hpbarbox.setSize(Vector2f(1000, 30));
	hpbarbox.setPosition(Vector2f(240, 20));

	armor = 0; //special
	armorbar.setFillColor(Color(0, 255, 255));
	armorbar.setSize(Vector2f(armor, 20));
	armorbar.setPosition(Vector2f(240, 60));

	armorbarbox.setFillColor(Color(200, 200, 200, 100));
	armorbarbox.setOutlineColor(Color(0, 0, 0, 200));
	armorbarbox.setOutlineThickness(2);
	armorbarbox.setSize(Vector2f(700, 20));
	armorbarbox.setPosition(Vector2f(240, 60));


	newgunText.setFont(font);
	newgunText.setString("NEW GUN");
	newgunText.setFillColor(Color::White);
	newgunText.setLetterSpacing(2);
	newgunText.setCharacterSize(30);

	outofammoText.setFont(font);
	outofammoText.setString("OUT OF AMMO");
	outofammoText.setFillColor(Color::White);
	outofammoText.setLetterSpacing(2);
	outofammoText.setCharacterSize(30);

	
	hpText.setFont(font);
	hpText.setFillColor(Color::Black);
	hpText.setLetterSpacing(2);
	hpText.setCharacterSize(23);
	hpText.setPosition(Vector2f(250, 20));

	armorText.setFont(font);
	armorText.setFillColor(Color::Black);
	armorText.setLetterSpacing(2);
	armorText.setCharacterSize(18);
	armorText.setPosition(Vector2f(250, 60));

	this->mode = 0; // default = 0, mg = 1;
	this->rowUpgrade = 0;


	readfile.open("Resource/Text/player.ini");

	if (readfile.is_open())
	{
		readfile >> playername;
		readfile.close();
	}

	playerText.setFont(font);
	playerText.setString(playername);
	playerText.setFillColor(Color::White);
	playerText.setLetterSpacing(2);
	playerText.setCharacterSize(20);
	playerText.setPosition(20+profile.getSize().x/2 - playerText.getGlobalBounds().width/2 , profile.getGlobalBounds().top + profile.getSize().y / 1.15);

	isStop = false;
}

Player::~Player()
{
}

void Player::PlayerInput()
{
	velocity.x = 0;
	velocity.y = 0;
	if (Keyboard::isKeyPressed(Keyboard::A)) { velocity.x -= speed; }
	if (Keyboard::isKeyPressed(Keyboard::D)) { velocity.x += speed; }
	if (Keyboard::isKeyPressed(Keyboard::W)) { velocity.y -= speed; }
	if (Keyboard::isKeyPressed(Keyboard::S)) { velocity.y += speed; }
	//Bullets
	if (bulletCount < bulletRate) { bulletCount++; isPush = false; }
	if (Mouse::isButtonPressed(Mouse::Left) && bulletCount >= bulletRate && isShot == false)
	{
		isShot = true;
		isPush = true;
		soundeffect_shoot.play();
		bulletCount = 0;
	}
	else if (!Mouse::isButtonPressed(Mouse::Left))
	{
		isShot = false;
		isPush = false;
	}
}

void Player::Update(const float& deltaTime, Vector2f aimDir)
{
	hpText.setString("HEALTH " + to_string(hp) + "/1000");
	armorText.setString("ARMOR " + to_string(armor) + "/700");

	if (isStop == true) 
	{
		velocity.x = 0;
		velocity.y = 0;
		isStop = false;
	}

	switchTime = 0.1;

	//Newgun
	if (mode == 0) {
		rowUpgrade = 0;
		bulletRate = 100;
	}
	else if (mode == 1) {
		rowUpgrade = 6;
		bulletRate = 5;
	}

/////////////////////////////////////////////// Animation //////////////////////////////////////////////////
	if (hp > 1000) {
		hp = 1000;
	}
	if (armor > 700) {
		armor = 700;
	}
	if (hp>=0) {
		hpbar.setSize(Vector2f(hp, 30));
	}
	if (armor>=0) {
		armorbar.setSize(Vector2f(armor, 20));
	}


	//Animations
	if (isAlive == true) {
		if (velocity.x == 0.f && velocity.y == 0.f)
		{
			//Stop walk
			row = 0 + rowUpgrade;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (soundeffect_shoot.getStatus() == 2)
				{
					if (aimDir.y > -100) { row = 2 + rowUpgrade; }
					else if (aimDir.y <= -100) { row = 3 + rowUpgrade; }
					switchTime = 0.2;
				}
			}
			if (aimDir.x > 0) { faceRight = true; }
			else if (aimDir.x < 0) { faceRight = false; }
		}
		else
		{
			//Walking
			row = 1 + rowUpgrade;
			if (soundeffect_walk.getStatus() == 0) { soundeffect_walk.play(); }
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (soundeffect_shoot.getStatus() == 2)
				{
					if (aimDir.y > -100) { row = 2 + rowUpgrade; }
					else if (aimDir.y <= -100) { row = 3 + rowUpgrade; }

					velocity.x = 0.f;
					velocity.y = 0.f;

					if (aimDir.x > 0) { faceRight = true; }
					else if (aimDir.x < 0) { faceRight = false; }
					switchTime = 0.2;
				}
				else
				{
					if (velocity.x > 0) { faceRight = true; }
					else if (velocity.x < 0) { faceRight = false; }
				}
			}
			else
			{
				if (velocity.x > 0) { faceRight = true; }
				else if (velocity.x < 0) { faceRight = false; }
			}
		}
		if (isNewgun == true)
		{
			mode = 1;
			totalTime += deltaTime;
		}
		animation.Update(row, deltaTime, faceRight, switchTime);

	}
	else {
		velocity.x = 0.f;
		velocity.y = 0.f;
		counterDead += deltaTime;
		if (counterDead <= switchTimeDead) 
		{
			row = 4 + rowUpgrade;
			animation.Update(row, deltaTime, faceRight, switchTimeDead);
		}
		else {
			row = 5 + rowUpgrade;
			animation.Update(row, deltaTime, faceRight, switchTimeDead);
		}

	}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	body.setTextureRect(animation.xyRect);
	
	hitbox.move(Vector2f(velocity * deltaTime));
	body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 30);

	newgunText.setPosition(Vector2f(hitbox.getPosition().x-90, hitbox.getPosition().y-100));
	outofammoText.setPosition(Vector2f(hitbox.getPosition().x - 90, hitbox.getPosition().y - 100));

	if (isDamage == true) 
	{
		UpdateChangeColor(deltaTime);
	}
}

//////////////////////////////////////// Bullet Player /////////////////////////////////////////////////////

//////////////////////////////////////////  Render  /////////////////////////////////////////////////////
void Player::Draw(RenderTarget& target) //RenderWindow& window
{
	
	target.draw(body);
	if (isAlive == true) 
	{
		if (isNewgun == true && totalTime < 3) {
			target.draw(newgunText);
		}
		else if (totalTime > 10 && totalTime < 13) {
			mode = 0;
			target.draw(outofammoText);
		}
		else if (totalTime >= 13) {
			mode = 0;
			isNewgun = false;
		}
	}
	//target.draw(hitbox);

}

void Player::DrawUI(RenderTarget& target)
{
	target.draw(hpbarbox);
	target.draw(hpbar);
	
	target.draw(armorbarbox);
	target.draw(armorbar);

	target.draw(hpText);
	target.draw(armorText);

	target.draw(profile);
	target.draw(playerText);

	target.draw(gunbox);

	if (mode == 0) 
	{
		target.draw(gun1);
		target.draw(gunText1);
	}
	else if (mode == 1)
	{
		target.draw(gun2);
		target.draw(gunText2);
	}


}


