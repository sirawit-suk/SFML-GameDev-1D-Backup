#include "LoadingState.h"

LoadingState::LoadingState(RenderWindow* window, stack<State*>* states) : State(window, states)
{
	bg.loadFromFile("Resource/Background/background6.jpg");
	background.setPosition(0, 0);
	background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&bg);

	instructText.setFont(font);
	instructText.setString("PRESS ENTER TO START NEXT LEVEL");
	instructText.setFillColor(Color::White);
	instructText.setLetterSpacing(2);
	instructText.setCharacterSize(50);
	instructText.setOrigin(instructText.getGlobalBounds().width/2, instructText.getGlobalBounds().height / 2);
	instructText.setPosition(Vector2f(window->getSize().x/2, 930));

	loadingText.setFont(font);
	loadingText.setString("LOADING...");
	loadingText.setFillColor(Color::White);
	loadingText.setLetterSpacing(2);
	loadingText.setCharacterSize(50);
	loadingText.setOrigin(loadingText.getGlobalBounds().width / 2, loadingText.getGlobalBounds().height / 2);
	loadingText.setPosition(Vector2f(window->getSize().x / 2, 930));

	view.setSize(Vector2f(window->getSize().x - 90.f, window->getSize().y - 90.f));
	view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));

}

LoadingState::~LoadingState()
{
	delete fade;
}

void LoadingState::UpdateButtons()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter) && getKeyTime() && isReady == true) {
		if (clicksound.getStatus() == 0) { clicksound.play(); }
		fade->isFade = true;
	}
}

void LoadingState::Update(const float& deltaTime, Event evnt)
{
	if (isInitial == true) {
		isInitial = false;
	}

	if (fade->isFade == true)
	{
		fade->Update(deltaTime);
		if (fade->isFadeDone == true) {
			isInitial = true;
			endState(); //From State.h
			states->push(new GameState2(window, states)); //From State.h
		}
	}
	else
	{
		if (fade->isBright == true) {
			fade->Update(deltaTime);
		}

		UpdateMousePositions();
		UpdateKeytime(deltaTime);
		UpdateButtons();

		view.setCenter(Vector2f(window->getSize().x / 2 + mousePosScreen.x * 0.02, window->getSize().y / 2 + mousePosScreen.y * 0.02));
	}

	totalTime += deltaTime;

	if (totalTime >= 10) {
		isReady = true;
	}

	if (isReady == true) {
		ChangeFadeText(deltaTime);
		instructText.setFillColor(Color(255, 255, 255, colorValue));
		loadingText.setFillColor(Color(1, 1, 1, 0));
	}
	else {
		ChangeFadeText(deltaTime);
		instructText.setFillColor(Color(1, 1, 1, 0));
		loadingText.setFillColor(Color(255, 255, 255, colorValue));
	}	
}

void LoadingState::Render(RenderTarget* target)
{
	if (!target) target = window;
	target->setView(view);
	target->draw(background);

	target->setView(target->getDefaultView());


	if (isReady == true) {
		target->draw(instructText);
	}
	else
	{
		target->draw(loadingText);
	}


	if (fade->isFade == true || fade->isBright == true) {
		fade->Draw(*target);
	}
	if (isInitial == true) {
		target->draw(black);
	}
	target->setView(view);
}
