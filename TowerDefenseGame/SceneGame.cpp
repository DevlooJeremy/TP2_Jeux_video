#include "SceneGame.h"
#include "ContentPipeline.h"

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

	}
}

void SceneGame::update()
{

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

	hud.draw(renderWindow);
	renderWindow.display();

}

bool SceneGame::unload()
{
	return true;
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