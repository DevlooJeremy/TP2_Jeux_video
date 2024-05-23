#include "Tower.h"
#include "ContentPipeline.h"

Tower::Tower()
{
}

Tower::~Tower()
{
	delete[] imagesMageAttack;
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