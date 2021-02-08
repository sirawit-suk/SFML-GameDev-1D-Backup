#include "ScoreboardState.h"

ScoreboardState::ScoreboardState(RenderWindow* window, stack<State*>* states) : State(window, states)
{
	bg.loadFromFile("Resource/Background/background3.jpg");
	background.setPosition(0, 0);
	background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&bg);

	view.setSize(Vector2f(window->getSize().x - 90.f, window->getSize().y - 90.f));
	view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));

	buttons.push_back(Button(window->getSize().x / 2-150, window->getSize().y / 2 +250, 300, 100, &this->font, "BACK", Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200)));

	this->totalTime = 0.f;

	initial();

	readfile.open("Resource/Text/score.ini");

	if (readfile.is_open())
	{
		for (int i = 0; i < 5; i++) {
			readfile >> names[i] >> kills[i] >> scores[i];
		}
	}
	readfile.close();

	for (size_t i = 0; i < 5; i++)
	{
		nameTexts[i].setFont(font);
		nameTexts[i].setFillColor(Color::White);
		nameTexts[i].setString(names[i]);
		nameTexts[i].setLetterSpacing(2);
		nameTexts[i].setCharacterSize(50);

		nameTexts[i].setPosition(Vector2f(view.getCenter().x - 400, view.getCenter().y - 300 + i * 100));

		killTexts[i].setFont(font);
		killTexts[i].setFillColor(Color::White);
		killTexts[i].setString(to_string(kills[i]));
		killTexts[i].setLetterSpacing(2);
		killTexts[i].setCharacterSize(50);

		killTexts[i].setPosition(Vector2f(view.getCenter().x +50, view.getCenter().y - 300 + i * 100));

		scoreTexts[i].setFont(font);
		scoreTexts[i].setFillColor(Color::White);
		scoreTexts[i].setString(to_string(scores[i]));
		scoreTexts[i].setLetterSpacing(2);
		scoreTexts[i].setCharacterSize(50);

		scoreTexts[i].setPosition(Vector2f(view.getCenter().x +250, view.getCenter().y - 300 + i * 100));
	}

	box.setSize(Vector2f(window->getSize().x / 2, window->getSize().y / 1.5));
	box.setPosition(Vector2f(view.getCenter().x - window->getSize().x / 2 + box.getSize().x/2, view.getCenter().y - window->getSize().y / 2 + 50));
	box.setFillColor(Color(0,0,0,100));

	scoreboardText.setFont(font);
	scoreboardText.setString("SCORE BOARD");
	scoreboardText.setFillColor(Color::White);
	scoreboardText.setLetterSpacing(2);
	scoreboardText.setCharacterSize(80);
	scoreboardText.setPosition(box.getPosition().x + box.getSize().x / 5.7, box.getPosition().y);

	NAME.setFont(font);
	NAME.setString("NAME");
	NAME.setFillColor(Color::White);
	NAME.setLetterSpacing(2);
	NAME.setCharacterSize(40);
	NAME.setPosition(box.getPosition().x +80 , box.getPosition().y+120);

	KILL.setFont(font);
	KILL.setString("KILL");
	KILL.setFillColor(Color::White);
	KILL.setLetterSpacing(2);
	KILL.setCharacterSize(40);
	KILL.setPosition(box.getPosition().x +520, box.getPosition().y + 120);

	SCORE.setFont(font);
	SCORE.setString("SCORE");
	SCORE.setFillColor(Color::White);
	SCORE.setLetterSpacing(2);
	SCORE.setCharacterSize(40);
	SCORE.setPosition(box.getPosition().x +720, box.getPosition().y + 120);

	isHover = false;
}

ScoreboardState::~ScoreboardState()
{
	delete fade;
	buttons.clear();
}

void ScoreboardState::UpdateButtons()
{
	if (buttons[0].isPressed() && getKeyTime())
	{
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
	}
	
	if (buttons[0].isHovered() && isHover == false)
	{
		typesound.play();
		isHover = true;
	}
	else if (!buttons[0].isHovered())
	{
		isHover = false;
	}
}

void ScoreboardState::Update(const float& deltaTime, Event evnt)
{
	if (isInitial == true) {
		isInitial = false;
	}

	if (fade->isFade == true) 
	{
		fade->Update(deltaTime);
		if (fade->isFadeDone == true) {
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
		for (Button& button : buttons)
		{
			button.Update(mousePosView);
		}
		UpdateKeytime(deltaTime);
		UpdateButtons();
	}
		
}

void ScoreboardState::Render(RenderTarget* target)
{
	if (!target) target = window;
	target->setView(view);
	target->draw(background);


	target->setView(target->getDefaultView());
	for (Button& button : buttons)
	{
		button.Draw(*target);
	}

	target->draw(box);

	target->draw(scoreboardText);
	for (size_t i = 0; i < 5; i++)
	{
		target->draw(nameTexts[i]);
		target->draw(scoreTexts[i]);
		target->draw(killTexts[i]);
	}

	target->draw(KILL);
	target->draw(NAME);
	target->draw(SCORE);


	if (fade->isFade == true || fade->isBright == true) {
		fade->Draw(*target);
	}
	if (isInitial == true) {
		target->draw(black);
	}

	target->setView(view);
}
