#include "NameState.h"

NameState::NameState(RenderWindow* window, stack<State*>* states) : State(window, states)
{
	backgroundsound.openFromFile("Resource/Sound/battlefield1sound2.wav");
	backgroundsound.setVolume(30);
	backgroundsound.setLoop(1);

	backgroundsound.play();

	bg.loadFromFile("Resource/Background/background2.jpg");
	background.setPosition(0, 0);
	background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&bg);

	view.setSize(Vector2f(window->getSize().x - 90.f, window->getSize().y - 90.f));
	view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));

	instructText.setFont(font);
	instructText.setString("PRESS ENTER TO START NEW GAME");
	instructText.setFillColor(Color::White);
	instructText.setLetterSpacing(2);
	instructText.setCharacterSize(50);
	instructText.setPosition(Vector2f(500, 930));

	i = 300;

	box.setPosition(view.getCenter().x, view.getCenter().y+i);
	box.setSize(Vector2f(450,70));
	box.setOrigin(Vector2f(box.getSize().x/2,box.getSize().y/2));
	box.setFillColor(Color(0,0,0,150));

	cursor.setSize(Vector2f(5,51));
	cursor.setOrigin(Vector2f(cursor.getSize().x / 2, cursor.getSize().y / 2));
	cursor.setFillColor(Color::White);

	playername.setFont(font);
	playername.setFillColor(Color::White);
	playername.setLetterSpacing(2);
	playername.setCharacterSize(45);
	playername.setPosition(Vector2f(view.getCenter().x-200, view.getCenter().y-25+i));

	cursor.setPosition(Vector2f(box.getGlobalBounds().left + playername.getGlobalBounds().width + 20, view.getCenter().y+i));

	this->isBlink = false;
	this->isReady = false;

	mode = 0;

	please.setFont(font);
	please.setString("INSERT YOUR NAME");
	please.setFillColor(Color::White);
	please.setLetterSpacing(2);
	please.setCharacterSize(35);
	please.setPosition(Vector2f(box.getGlobalBounds().left + 30, view.getCenter().y-100+i));

	fade->setValue = 25;
}

NameState::~NameState()
{
	delete fade;
}

void NameState::UpdateSFMLEvent(const float& deltaTime, Event evnt)
{
	switch (evnt.type)
	{
		case Event::TextEntered:
			if (lastchar != evnt.text.unicode && input.length() < 12 &&
				(evnt.text.unicode >= 'a' && evnt.text.unicode <= 'z' ||
					evnt.text.unicode >= 'A' && evnt.text.unicode <= 'Z' ||
					evnt.text.unicode >= '0' && evnt.text.unicode <= '9'))
			{
				lastchar = evnt.text.unicode;
				input += evnt.text.unicode;
				cursor.setPosition(Vector2f(box.getGlobalBounds().left + playername.getGlobalBounds().width + 70, view.getCenter().y-11 + i));
				typesound.play();
			}
			if (lastchar != evnt.text.unicode && evnt.text.unicode == 8 && input.length() > 0)
			{
				lastchar = evnt.text.unicode;
				input.erase(input.length() - 1);
				cursor.setPosition(Vector2f(box.getGlobalBounds().left + playername.getGlobalBounds().width +20,view.getCenter().y-11 + i));
				typesound.play();
			}
			playername.setString(input);
			break;

		case Event::KeyReleased:
			if (lastchar != ' ')
			{
				lastchar = ' ';
			}
			break;
	}
}

void NameState::UpdateName()
{
	writefile.open("Resource/Text/player.ini");
	if (writefile.is_open())
	{
		writefile << input;
	}
	writefile.close();
}

void NameState::UpdateButtons()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter) && getKeyTime() && isReady == true) { 
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
		mode = 0;

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && getKeyTime()) {
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
		mode = 1;
	}

}

void NameState::Update(const float& deltaTime, Event evnt)
{
	if (input.length() == 0) {
		isReady = false;
	}
	else if (input.length() > 0) {
		isReady = true;
	}

	UpdateSFMLEvent(deltaTime, evnt);

	if (isInitial == true) {
		isInitial = false;
	}

	if (fade->isFade == true)
	{
		fade->Update(deltaTime);
		if (fade->isFadeDone == true && mode == 0) {
			UpdateName();
			backgroundsound.stop();
			isInitial = true;
			endState(); //From State.h
			states->push(new GameState(window, states)); //From State.h
		}
		if (fade->isFadeDone == true && mode == 1) {
			endState(); //From State.h
		}
	}
	else
	{
		if (fade->isBright == true) {
			fade->Update(deltaTime);
		}

		view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));

		UpdateMousePositions();
		UpdateKeytime(deltaTime);
		UpdateButtons();
	}

	if (totalTime >= 0.3) {
		totalTime = 0;
		isBlink = !isBlink;
	}

	totalTime += deltaTime;

	if (isReady == true) {
		ChangeFadeText(deltaTime);
		instructText.setFillColor(Color(255,255,255,colorValue));
	}
	else {
		instructText.setFillColor(Color(1, 1, 1, 0));
	}

}

void NameState::Render(RenderTarget* target) 
{
	if (!target) target = window;
	target->setView(view);
	target->draw(background);

	target->setView(target->getDefaultView());




	target->draw(box);
	if (isBlink == false) {
		target->draw(cursor);
	}
	target->draw(playername);
	target->draw(please);




	target->draw(instructText);
	if (fade->isFade == true || fade->isBright == true) {
		fade->Draw(*target);
	}
	if (isInitial == true) {
		target->draw(black);
	}

	target->setView(view);
}
