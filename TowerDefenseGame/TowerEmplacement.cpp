#include "TowerEmplacement.h"
#include "ContentPipeline.h"
#include "SceneGame.h"
#include "Tower.h"

TowerEmplacement::TowerEmplacement()
{
	Subject::addObserver(this);
}

void TowerEmplacement::init(const Vector2f& position) {
	setTexture(ContentPipeline::getInstance().getTowerEmplacementTexture());
	setPosition(position);
	activate();
}

void TowerEmplacement::notify(Subject* subject) {
	if (typeid(*subject) == typeid(SceneGame))
	{
		if (isActive())
		{
			SceneGame* game = static_cast<SceneGame*>(subject);
			if (mouseInBound(game->getMousePosition()) && (game->getInstruction() == SceneGame::ARCHER_TOWER || game->getInstruction() == SceneGame::MAGE_TOWER))
			{
				deactivate();
			}
		}
	}
	else if (typeid(*subject) == typeid(Tower))
	{
		if (!isActive())
		{
			Tower* tower = static_cast<Tower*>(subject);
			if (!tower->isActive() && tower->getPosition() == getPosition())
			{
				deactivate();
			}
		}
	}
}

bool TowerEmplacement::mouseInBound(const Vector2f mousePosition) const {
	FloatRect bounds = getGlobalBounds();
	if (mousePosition.x >= bounds.left && mousePosition.x <= bounds.left + bounds.width &&
		mousePosition.y >= bounds.top && mousePosition.y <= bounds.top + bounds.height)
	{
		return true;
	}
	return false;
}