#include "SceneGame.h"
#include "ContentPipeline.h"
#include "Subject.h"

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event, int currentWave) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->currentWave = currentWave;
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
	if (currentWave % 2 != 0)
		mapNbr = 1;
	else
		mapNbr = 2;

	if (mapNbr == 1)
		map.setTexture(ContentPipeline::getInstance().getMapTexture(Maps::map1));
	else
		map.setTexture(ContentPipeline::getInstance().getMapTexture(Maps::map2));

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont());
	setupWaypoints();
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].init(&waypoints[0]);
		Subject::addObserver(&demons[i]);
	}


	initTowers();

	return true;
}

void SceneGame::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				inputs.mouseLeftButtonClicked = true;
				inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
			}
		}

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
	manageLeftClick();
	manageDemon();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.draw(map);

	for (int i = 0; i < currentMapMaxNbrOfTower; i++)
	{
		emplacements[i].draw(renderWindow);
		towers[i].draw(renderWindow);
		towers[i + currentMapMaxNbrOfTower].draw(renderWindow);
	}

	towers[KING_TOWER_ARRAY_POSITION].draw(renderWindow);

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

void SceneGame::manageLeftClick() {
	if (inputs.mouseLeftButtonClicked)
	{
		switch (instruction)
		{
		case ARCHER_TOWER:
			manageArcherPlacement();
			break;

		case MAGE_TOWER:
			manageMagePlacement();
			break;

		case PLAGUE:
		
			break;

		case SACRED_LIGHT:
		
			break;

		default:
			break;
		}
	}
}

void SceneGame::manageArcherPlacement() {

}

void SceneGame::manageMagePlacement() {

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

void SceneGame::initTowers() {
	if (mapNbr == 1)
	{
		currentMapMaxNbrOfTower = 8;
		towers[KING_TOWER_ARRAY_POSITION].init(Tower::KING_TOWER_SPRITE_NBR, KING_TOWER_POSITION_MAP1);
		for (int i = 0; i < currentMapMaxNbrOfTower; i++)
		{
			emplacements[i].init(TOWER_EMPLACEMENTS_MAP1[i]);
			towers[i].init(Tower::ARCHER_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP1[i]);
			towers[i + currentMapMaxNbrOfTower].init(Tower::MAGE_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP1[i]);
		}
	}
	else
	{
		currentMapMaxNbrOfTower = NBR_MAX_TOWER - 1;
		for (int i = 0; i < currentMapMaxNbrOfTower; i++)
		{
			emplacements[i].init(TOWER_EMPLACEMENTS_MAP2[i]);
			towers[i].init(1, TOWER_EMPLACEMENTS_MAP2[i]);
			towers[i + currentMapMaxNbrOfTower].init(2, TOWER_EMPLACEMENTS_MAP2[i]);
		}
	}
}