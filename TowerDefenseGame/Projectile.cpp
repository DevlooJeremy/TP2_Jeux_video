#include "Projectile.h"
#include "ContentPipeline.h"
#include <iostream>

Projectile::Projectile()
{
}

Projectile::~Projectile() {
}

void Projectile::init(const int spriteNbr) {
	switch (spriteNbr)
	{
	case ARROW_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getArrowTexture());
		speed = ARROW_SPEED;
		maxDamage = ARROW_MAX_DAMAGE;
		break;
	case BLAST_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getBlastTexture());
		speed = BLAST_SPEED;
		maxDamage = BLAST_MAX_DAMAGE;
		break;
	case FIREBALL_SPRITE_NBR:
		setTexture(ContentPipeline::getInstance().getFireballTexture());
		speed = FIREBALL_SPEED;
		maxDamage = FIREBALL_MAX_DAMAGE;
		break;

	default:
		break;
	}

	this->spriteNbr = spriteNbr;
}

void Projectile::shoot(GameObject* target, const Vector2f origin) {
	this->target = target;
	setPosition(origin);
	activate();
}

void Projectile::follow(const float deltaTime) {
	if (isActive())
	{
		if (!target->isActive())
		{
			deactivate();
		}
		else
		{
			float moveSpeed = deltaTime * speed;
			Vector2f targetPosition = target->getPosition();
			float moveAngle = atan2f((targetPosition.y - getPosition().y), (targetPosition.x - getPosition().x));

			move(cos(moveAngle) * moveSpeed, sin(moveAngle) * moveSpeed);

			if (getCollisionCircle().checkCollision(target->getCollisionCircle()))
			{
				target->damage(getRndDamage());
				deactivate();
				target = nullptr;
			}
		}
	}
}

int Projectile::getRndDamage() const {
	return rand() % (maxDamage - MIN_DAMAGE + 1) + MIN_DAMAGE;
}