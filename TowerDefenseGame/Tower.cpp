#include "Tower.h"
#include "ContentPipeline.h"
#include "SceneGame.h"
#include "TowerEmplacement.h"

Tower::Tower()
{
	Subject::addObserver(this);
}

Tower::~Tower()
{
	if (imagesMageAttack != nullptr)
	{
		delete[] imagesMageAttack;
	}
}

void Tower::init(const int spriteNbr, const Vector2f& position) {
	switch (spriteNbr)
	{
	case KING_TOWER_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getKingTowerTexture());
		setHealth(KING_MAX_HEALTH);
		activate();
		break;
	case ARCHER_TOWER_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getArcherTowerTexture());
		setHealth(MAX_HEALTH);
		break;
	case MAGE_TOWER_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getMageTowerTexture());
		setHealth(MAX_HEALTH);
		setupMageAnims();
		break;

	default:
		break;
	}	

	this->spriteNbr = spriteNbr;
	setPosition(position);
}

void Tower::setupMageAnims() {
	imagesMageAttack = new IntRect[MAGE_ATTACK_ANIM];

	for (int i = 0; i < MAGE_ATTACK_ANIM; i++)
	{
		imagesMageAttack[i].left = MAGE_RECTANGLE_SIZE * i;
		imagesMageAttack[i].top = 0;
		imagesMageAttack[i].height = MAGE_RECTANGLE_SIZE;
		imagesMageAttack[i].width = MAGE_RECTANGLE_SIZE;
	}

	setTextureRect(imagesMageAttack[0]);
	setOrigin(MAGE_RECTANGLE_SIZE / 2, MAGE_RECTANGLE_SIZE / 2);
}

void Tower::notify(Subject* subject) {
	if (typeid(*subject) == typeid(SceneGame))
	{
		if (!isActive())
		{
			SceneGame* game = static_cast<SceneGame*>(subject);
			SceneGame::Instruction gameInstruction = game->getInstruction();
			if (mouseInBound(game->getMousePosition()) && !towerBuiltOnPosition)
			{
				switch (gameInstruction)
				{
				case SceneGame::Instruction::ARCHER_TOWER:
					if (spriteNbr == ARCHER_TOWER_SPRITE_NBR)
						activate();
					else
						towerBuiltOnPosition = true;
					break;
				case SceneGame::Instruction::MAGE_TOWER:
					if (spriteNbr == MAGE_TOWER_SPRITE_NBR)
						activate();
					else
						towerBuiltOnPosition = true;
					break;
				default:
					break;
				}
			}
		}
	}
	else if (typeid(*subject) == typeid(TowerEmplacement))
	{
		TowerEmplacement* emplacement = static_cast<TowerEmplacement*>(subject);
		if (getPosition() == emplacement->getPosition())
		{
			towerBuiltOnPosition = false;
		}
	}
}

void Tower::build() {
	setHealth(MAX_HEALTH);
	activate();
}

bool Tower::mouseInBound(const Vector2f mousePosition) const {
	FloatRect bounds = getGlobalBounds();
	if (mousePosition.x >= bounds.left && mousePosition.x <= bounds.left+bounds.width &&
		mousePosition.y >= bounds.top && mousePosition.y <= bounds.top + bounds.height)
	{
		return true;
	}
	return false;
}