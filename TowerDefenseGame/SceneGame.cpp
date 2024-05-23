#include "SceneGame.h"
#include "ContentPipeline.h"
#include "Subject.h"

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
}

Scene::scenes SceneGame::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;

	return transitionToScene;
}

bool SceneGame::init()
{	
	map.setTexture(ContentPipeline::getInstance().getMapTexture(Maps::map1));

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont());
	setupWaypoints();
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].init(&waypoints[0]);
		Subject::addObserver(&demons[i]);
	}


	return true;
}

void SceneGame::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.scancode == Keyboard::Scan::A) //Plague
			{
			
			}

			if (event.key.scancode == Keyboard::Scan::S) //Sacred light
			{
				
			}
		}
	}
}

void SceneGame::update()
{
	manageDemon();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.draw(map);
	for (size_t i = 0; i < 11; i++)
	{
		renderWindow.draw(waypoints[i]);
	}
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].draw(renderWindow);
	}
	hud.draw(renderWindow);
	renderWindow.display();
}

bool SceneGame::unload()
{

	Subject::removeAllObservers();
	return true;
}

void SceneGame::setupWaypoints() 
{
	waypoints[0].setPosition(610, 8);
	waypoints[1].setPosition(630, 222);
	waypoints[2].setPosition(595, 444);
	waypoints[3].setPosition(478, 514);
	waypoints[4].setPosition(320, 558);
	waypoints[5].setPosition(260, 620);
	waypoints[6].setPosition(280, 720);
	waypoints[7].setPosition(348, 812);
	waypoints[8].setPosition(720, 830);
	waypoints[9].setPosition(968, 850);
	waypoints[10].setPosition(1110, 682);

	for (size_t i = 0; i < NBR_WAYPOINTS - 1; i++)
	{
		waypoints[i].setNext(&waypoints[i + 1]);
	}
}

void SceneGame::manageDemon()
{
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].manageDemon(deltaTime);
	}
	spawnDemon();
}

void SceneGame::spawnDemon()
{
	spawnTimer += deltaTime;
	if (spawnTimer >= 1.1f)
	{
		spawnTimer = 0.0f;
		for (size_t i = 0; i < NBR_DEMON; i++)
		{
			if (!demons[i].isActive()) 
			{
				demons[i].spawn();
				break;
			}
		}
	}
}