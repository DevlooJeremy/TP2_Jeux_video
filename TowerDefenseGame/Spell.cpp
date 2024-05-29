#include "Spell.h"
#include "ContentPipeline.h"
#include <iostream>

bool Spell::sacredLightCasted = false;
bool Spell::plagueCasted = false;

Spell::Spell()
{
	rune.setTexture(ContentPipeline::getInstance().getRunesTexture());
	rune.setOrigin(ContentPipeline::getInstance().getRunesTexture().getSize().x / 2, ContentPipeline::getInstance().getRunesTexture().getSize().y / 2);
}

void Spell::manageSpell(float deltaTime)
{
	if (!isActive()) return;

	manageDuration(deltaTime);
	manageRunes();

}

void Spell::manageDuration(const float deltaTime)
{
	if (timer >= 5.0f)
	{
		deactivate();
		if (spellType == SpellType::SACRED_LIGHT) Spell::sacredLightCasted = false;
		else if (spellType == SpellType::PLAGUE) Spell::plagueCasted = false;
		notifyAllObservers();
	}
	else
	{
		timer += deltaTime;
	}
}

void Spell::manageRunes()
{
	rune.rotate(0.5 + timer);
}

float Spell::getRange() const
{
	return RANGE;
}

void  Spell::castSacredLight(const Vector2f position)
{
	if (Spell::sacredLightCasted) return;
	Spell::sacredLightCasted = true;
	activate();
	spellType = SpellType::SACRED_LIGHT;
	setTexture(ContentPipeline::getInstance().getSacredLightTexture());	
	setOrigin(ContentPipeline::getInstance().getSacredLightTexture().getSize().x / 2, ContentPipeline::getInstance().getSacredLightTexture().getSize().y / 2);
	setHealing();
	cast(position);
}

void Spell::castPlague(const Vector2f position)
{
	if (Spell::plagueCasted) return;
	Spell::plagueCasted = true;
	activate();
	spellType = SpellType::PLAGUE;
	setTexture(ContentPipeline::getInstance().getPlagueTexture());
	setOrigin(ContentPipeline::getInstance().getPlagueTexture().getSize().x / 2, ContentPipeline::getInstance().getPlagueTexture().getSize().y / 2);
	cast(position);
}

void Spell::cast(Vector2f position)
{
	timer = 0.0f;
	setPosition(position);
	rune.setPosition(position);
	setDamage();
	notifyAllObservers();
}

Spell::SpellType Spell::getSpellType()
{
	return spellType;
}

void Spell::draw(RenderWindow& renderWindow) const
{
	GameObject::draw(renderWindow);
	if (isActive()) renderWindow.draw(rune);
}

void Spell::setDamage()
{
	if (spellType == SpellType::PLAGUE)
	{
		damage = std::rand() % MAXIMUM_PLAGUE_DAMAGE + MIN_DAMAGE;
	}
	else if (spellType == SpellType::SACRED_LIGHT)
	{
		damage = std::rand() % MAXIMUM_SACRED_LIGHT_DAMAGE + MIN_DAMAGE;
	}
}

void Spell::setHealing()
{
	heal = rand() % MAXIMUM_HEAL + MINIMUM_HEAL;
}

int Spell::getDamage() const
{
	return damage;
}

int Spell::getHealing() const
{
	return heal;
}

int Spell::getAttackSpeedBonus() const
{
	return ATTACK_SPEED_BONUS;
}

int Spell::getBonusDamage() const
{
	return BONUS_DAMAGE;
}

float Spell::getSlow() const
{
	return SLOW;
}