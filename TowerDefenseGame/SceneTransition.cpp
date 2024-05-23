#include "SceneTransition.h"
#include "ContentPipeline.h"
#include <iostream>

SceneTransition::SceneTransition(RenderWindow& renderWindow, Event& event, int currentWave) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->currentWave = currentWave;
}

Scene::scenes SceneTransition::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	return transitionToScene;
}

bool SceneTransition::init()
{
	if (currentWave == 1)
	{
		message.setString("Minions of the Dark Lord march on our lands.\n\n             Defend the King's Tower!\n\n                           Wave 1");
		message.setCharacterSize(60);
	}
	else {
		message.setString("Wave " + currentWave);
		message.setCharacterSize(80);
	}

	displayTime = MAX_DISPLAY_TIME;

	message.setFont(ContentPipeline::getInstance().getComiciFont());
	message.setColor(Color::White);
	message.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
	return true;
}

void SceneTransition::getInputs()
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed) exitGame();
	}
}

void SceneTransition::update()
{
	displayTime -= deltaTime;
	if (displayTime <= 0)
	{
		startWave();
	}
}

void SceneTransition::draw()
{
	renderWindow.clear();
	renderWindow.draw(message);
	renderWindow.display();
}

bool SceneTransition::unload()
{
	return true;
}

void SceneTransition::startWave() {
	isRunning = false;
	transitionToScene = Scene::scenes::LEVEL1;
}