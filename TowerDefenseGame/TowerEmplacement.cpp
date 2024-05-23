#include "TowerEmplacement.h"
#include "ContentPipeline.h"

TowerEmplacement::TowerEmplacement()
{
}

void TowerEmplacement::init(const Vector2f& position) {
	setTexture(ContentPipeline::getInstance().getTowerEmplacementTexture());
	setPosition(position);
	activate();
}