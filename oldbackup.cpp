#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "Animation.h"
using namespace std;
using namespace sf;

int main(){

	RenderWindow window(VideoMode(1920, 1080), "World War II");
	window.setFramerateLimit(30);
	
	RectangleShape player(Vector2f(120.0f,120.0f));
	//player.scale(Vector2f(2.5, 2.5));
	player.setPosition(200.0f,200.0f);
	
	Texture playerTexture;
	playerTexture.loadFromFile("images/WWII AMERICAN MARINE.png");
	player.setTexture(&playerTexture);	
	
	Animation animation(Vector2u(240,1140), 0.2f);

	float deltaTime = 0.0f;
	Clock clock;
	
	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();
		
		Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				cout << "W: " << evnt.size.width << "H: " << evnt.size.height << endl;
				break;
			case Event::LostFocus:
				cout << "Lost Focus" << endl;
				break;
			case Event::GainedFocus:
				cout << "Gain Focus" << endl;
				break;
			}
		}
		
		animation.Update(deltaTime);
		player.setTextureRect(animation.xyRect);
		

		window.clear();
		window.draw(player);
		window.display();

	}

	return 0;
}












/*
case Event::MouseButtonPressed:
					if (event.key.code == Mouse::Left) cout << "Left Pressed" << endl;
					if (event.key.code == Mouse::Right) cout << "Right Pressed" << endl;
					break;
				case Event::MouseButtonReleased:
					if (event.key.code == Mouse::Left) cout << "Left Released" << endl;
					if (event.key.code == Mouse::Right) cout << "Right Released" << endl;
					break;
				case Event::MouseWheelMoved:
					cout << "Mouse Scrolled " << event.mouseWheel.delta << endl;
					break;
				case Event::MouseMoved:
					cout << "Mouse has been moved ";
					cout << "x : " << event.mouseMove.x << "y: " << event.mouseMove.y <<endl;
					break;
				case Event::KeyPressed:
					if (event.key.code == Keyboard::W) cout << "W was Pressed" << endl;
					if (event.key.code == Keyboard::S) cout << "S was Pressed" << endl;
					if (event.key.code == Keyboard::A) cout << "A was Pressed" << endl;
					if (event.key.code == Keyboard::D) cout << "D was Pressed" << endl;
					if (event.key.code == Keyboard::Space) cout << "Space was Pressed" << endl;
					break;
*/

/*
	int setX_position = 670;
	int setY_position = 350;
	if (!texture.loadFromFile("images/WWII AMERICAN MARINE.png")) {
		cout << "Error loading Soilder texture" << endl;

		/*
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(240,1140,60,60)); //240

	float size = 2.5;
	sprite.scale(Vector2f(size,size));
	sprite.setPosition(Vector2f(setX_position,setY_position));
	
	//sprite.setColor(Color(255, 0, 0));
	//sprite.setOrigin(Vector2f(30,30));

		float x_position = 0;
		float y_position = 0;
		float time = 20;
		int x_texture[4] = {90,140,190,240};
		bool state = 0;
		
	}
	*/

	/*
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i mousePos = Mouse::getPosition(window);
				sprite.setPosition((float)mousePos.x, (float)mousePos.y);
			}

			if (Keyboard::isKeyPressed(Keyboard::W)) {
				y_position = -time; i++; //cout << "W" << endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				y_position = time; i++; //cout << "S" << endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				x_position = -time; i++; //cout << "A" << endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				x_position = time; i++; //cout << "D" << endl;
			}
			i = i % 3;
			sprite.move(Vector2f(x_position, y_position));
			if (x_position == 0 && y_position == 0) i = 3;

			sprite.setTextureRect(IntRect(x_texture[i], 1140, 60, 60));

			cout << "X : " << sprite.getPosition().x << "Y : " << sprite.getPosition().y << endl;
			*/
			
			
		#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation{
public:
	Animation(Vector2u coordinate, float switchTime);
	~Animation();

	void Update(float deltaTime);
	
public:
	IntRect xyRect;

private:
	
	Vector2u coordinate;
	Vector2f currentImage;

	int i;
	int walk[4] = { 90,140,190 };
	float totalTime;
	float switchTime;

	

};


#include "Animation.h"


Animation::Animation(Vector2u coordinate, float switchTime)
{
	this->switchTime = switchTime;
	this->coordinate = coordinate;
	totalTime = 0.0f;
	i = 0;

	xyRect.width = 60;
	xyRect.height = 60;
	//xyRect.width = texture->getSize().x / float(imageCount.x);
	//xyRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation(){}

void Animation::Update(float deltaTime)
{

	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		i++;
		if (i >= 3) {
			i = 0;
		}
	}

	xyRect.left = walk[i];
	xyRect.top = coordinate.y;
}


