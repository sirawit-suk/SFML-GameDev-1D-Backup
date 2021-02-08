#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font , View& view)
	:font(font)
{

	background.setSize(Vector2f(window.getSize().x, window.getSize().y));
	background.setFillColor(Color(20,20,20,100));

	windowbox.setSize(Vector2f(window.getSize().x/2.5, window.getSize().y/3));
	windowbox.setFillColor(Color(20, 20, 20, 200));

	this->menuText.setFont(font);
	this->menuText.setFillColor(Color::White);
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSE GAME");
	
	this->areyousureText.setFont(font);
	this->areyousureText.setFillColor(Color::White);
	this->areyousureText.setCharacterSize(23);
	this->areyousureText.setString("ARE YOU SURE YOU WANT TO GO BACK TO MAIN MENU?");
	
	initialPause(window, view);
}

PauseMenu::~PauseMenu()
{
	buttons.clear();

}

void PauseMenu::addButton(float x, float y, const string text)
{
	buttons.push_back(Button(x, y, 250, 80, &this->font, text, Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200)));
}

void PauseMenu::initialPause(RenderWindow& window, View& view)
{
	background.setPosition(Vector2f(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2));
	windowbox.setPosition(Vector2f(view.getCenter().x - window.getSize().x / 2 + windowbox.getSize().x / 1.4, view.getCenter().y - window.getSize().y / 2 + windowbox.getSize().y));
	this->menuText.setPosition(windowbox.getPosition().x + windowbox.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f, windowbox.getPosition().y + 50);
	this->areyousureText.setPosition(windowbox.getPosition().x + windowbox.getSize().x / 2.f - areyousureText.getGlobalBounds().width / 2.f, windowbox.getPosition().y + 150);
}

void PauseMenu::Update(Vector2f& mousePosView)
{
	for (Button& button: buttons) 
	{
		button.Update(mousePosView);
	}
}

void PauseMenu::Draw(RenderTarget& target)
{
	target.draw(background);
	target.draw(windowbox);

	for (Button& button : buttons) 
	{
		button.Draw(target);
	}

	target.draw(menuText);
	target.draw(areyousureText);
}
