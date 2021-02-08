#include "MainMenuState.h"

MainMenuState::MainMenuState(RenderWindow* window, stack<State*>* states) : State(window, states)
{
	title.setFont(font);
	title.setString("WORLD WAR I : ROAD TO CAMBRAI");
	title.setLetterSpacing(2);
	title.setFillColor(Color::White);
	title.setCharacterSize(80);
	title.setPosition(Vector2f(200,200));

	mynumber.setFont(font);
	mynumber.setString("62010948");
	mynumber.setLetterSpacing(2);
	mynumber.setFillColor(Color::White);
	mynumber.setCharacterSize(40);
	mynumber.setPosition(Vector2f(50, 900));

	myname.setFont(font);
	myname.setString("Sirawit Sukwattanavit");
	myname.setLetterSpacing(2);
	myname.setFillColor(Color::White);
	myname.setCharacterSize(30);
	myname.setPosition(Vector2f(50, 950));

	myDegree.setFont(font);
	myDegree.setString("COMPUTER ENGINEERING KMITL");
	myDegree.setLetterSpacing(2);
	myDegree.setFillColor(Color::White);
	myDegree.setCharacterSize(25);
	myDegree.setPosition(Vector2f(50, 1000));

	date.setFont(font);
	date.setString("26 NOV 2019");
	date.setLetterSpacing(2);
	date.setFillColor(Color::White);
	date.setCharacterSize(25);
	date.setPosition(Vector2f(1680, 1000));

	version.setFont(font);
	version.setString("RELEASE V.1");
	version.setLetterSpacing(2);
	version.setFillColor(Color::White);
	version.setCharacterSize(25);
	version.setPosition(Vector2f(1705, 955));

	background_Sound.openFromFile("Resource/Sound/battlefield1sound.wav");
	background_Sound.setLoop(1);

	bg.loadFromFile("Resource/Background/background5.jpg");
	background.setPosition(0, 0);
	background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&bg);

	buttons.push_back(Button(window->getSize().x / 2-150, window->getSize().y / 2 -50, 350, 100 , &this->font, "NEW GAME", Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200)));
	buttons.push_back(Button(window->getSize().x / 2-150, window->getSize().y / 2 +100, 350, 100 , &this->font, "SCORE BOARD", Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200)));
	buttons.push_back(Button(window->getSize().x / 2 - 150, window->getSize().y / 2 + 250, 350, 100, &this->font, "EXIT GAME", Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200)));

	view.setSize(Vector2f(window->getSize().x-90.f, window->getSize().y-90.f));
	view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));

	this->totalTime = 0.f;
	mode = 0;

	isHover0 = false;
	isHover1 = false;
	isHover2 = false;
}

MainMenuState::~MainMenuState()
{
	buttons.clear();
}


void MainMenuState::UpdateButtons(const float& deltaTime)
{

	if (buttons[0].isPressed() && getKeyTime())
	{
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
		mode = 0;
	}
	if (buttons[1].isPressed() && getKeyTime())
	{
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
		mode = 1;
	}
	if (buttons[2].isPressed() && getKeyTime())
	{
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
		mode = 2;
	}

	if (buttons[0].isHovered() && isHover0 == false)
	{
		typesound.play();
		isHover0 = true;
	}
	else if(!buttons[0].isHovered())
	{
		isHover0 = false;
	}

	if (buttons[1].isHovered() && isHover1 == false)
	{
		typesound.play();
		isHover1 = true;
	}
	else if (!buttons[1].isHovered())
	{
		isHover1 = false;
	}

	if (buttons[2].isHovered() && isHover2 == false)
	{
		typesound.play();
		isHover2 = true;
	}
	else if (!buttons[2].isHovered())
	{
		isHover2 = false;
	}

}

void MainMenuState::Update(const float& deltaTime, Event evnt)
{
	if (isInitial == true) {
		initial();
		isInitial = false;
	}

	if (fade->isFade == true ) 
	{
		fade->Update(deltaTime);
		if (fade->isFadeDone == true && mode == 0) {
			background_Sound.stop();
			delete fade;
			isInitial = true;
			states->push(new NameState(window, states)); //From State.h
			//states->push(new GameState(window, states)); //From State.h
		}
		if (fade->isFadeDone == true && mode == 1) {
			delete fade;
			isInitial = true;
			states->push(new ScoreboardState(window, states)); //From State.h
		}
		if (fade->isFadeDone == true && mode == 2) {
			delete fade;
			isInitial = true;
			endState(); //From State.h
		}
	}
	else
	{
		if (fade->isBright == true) {
			fade->Update(deltaTime);
		}

		if (background_Sound.getStatus() == 0) {
			background_Sound.play(); //Play Musics
		}

		view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));
		UpdateMousePositions();
		for (Button& button : buttons)
		{
			button.Update(mousePosView);
		}
		UpdateKeytime(deltaTime);
		UpdateButtons(deltaTime);
	}

}

void MainMenuState::Render(RenderTarget* target)
{
	if (!target) target = window;
	target->setView(view);
	target->draw(background);

	target->setView(target->getDefaultView());
	target->draw(title);

	target->draw(myname);
	target->draw(mynumber);
	target->draw(myDegree);

	target->draw(version);
	target->draw(date);

	for (Button& button : buttons)
	{
		button.Draw(*target);
	}
	//cout << fade->isFade << " F" << fade->isBright << " B" << endl;
	if (fade->isFade == true || fade->isBright == true) {
		fade->Draw(*target);
	}
	if (isInitial == true) {
		target->draw(black);
	}
	target->setView(view);

}
