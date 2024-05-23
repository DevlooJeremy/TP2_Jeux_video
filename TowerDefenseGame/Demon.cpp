#include "Demon.h"
#include "ContentPipeline.h"
#include <iostream>

Demon::Demon()
{
}

Demon::~Demon()
{
	delete[] imagesFlying;
	delete[] imagesDying;
}

bool Demon::init(Waypoint* waypoint)
{
	this->waypoint = waypoint;
	texture = ContentPipeline::getInstance().getDemonTexture();
	setTexture(texture);
	setOrigin(texture.getSize().x / 10, texture.getSize().y / 4);
	attackBuffer = ContentPipeline::getInstance().getDemonAttackSoundBuffer();
	attackSound.setBuffer(attackBuffer);
	setImages();

	return true;
}

void Demon::setImages()
{
	imagesFlying = new IntRect[NBR_ANIM_IMAGES];
	imagesDying = new IntRect[NBR_ANIM_IMAGES];

	//Rectangles d'animation pour le vol.
	for (size_t i = 0; i < NBR_ANIM_IMAGES; i++)
	{
		imagesFlying[i].left = (texture.getSize().x / 5) * i;
		imagesFlying[i].top = 0;
		imagesFlying[i].height = texture.getSize().y / 2;
		imagesFlying[i].width = texture.getSize().x / 5;
	}

	//Rectangles d'animation pour la mort.
	for (size_t i = 0; i < NBR_ANIM_IMAGES; i++)
	{
		imagesDying[i].left = (texture.getSize().x / 5) * i;
		imagesDying[i].top = texture.getSize().y / 2;
		imagesDying[i].height = texture.getSize().y / 2;
		imagesDying[i].width = texture.getSize().x / 5;
	}

	//Initialisation de la première frame.
	setTextureRect(imagesFlying[0]);
}

void Demon::manageDemon(float deltaTime)
{
	if (!isActive()) return;
	moveTowardsWaypoint(deltaTime);
	manageAnimation(deltaTime);
	changeWaypoints();
}

void Demon::moveTowardsWaypoint(float deltaTime)
{
	if (animationState != AnimationState::DEATH) setAnimationState(AnimationState::FLY);
	float moveSpeed = speed * 60;
	float angle = atan2f(waypoint->getPosition().y - getPosition().y,waypoint->getPosition().x - getPosition().x);
	move(cos(angle) * moveSpeed * deltaTime,sin(angle) * moveSpeed * deltaTime);
}

void Demon::changeWaypoints()
{
	if (waypoint->getNext() == nullptr) return;
	Vector2f distance = waypoint->getPosition() - getPosition();
	if (std::abs(distance.x) < DEAD_ZONE && std::abs(distance.y) < DEAD_ZONE) waypoint = waypoint->getNext();
}

void Demon::manageAnimation(const float deltaTime)
{
	if (animationState == AnimationState::FLY) runAnimation(deltaTime, TIME_PER_FRAME, NBR_ANIM_IMAGES, false, imagesFlying);
	else if (animationState == AnimationState::DEATH) runAnimation(deltaTime, TIME_PER_FRAME, NBR_ANIM_IMAGES, true, imagesDying);
}

void Demon::runAnimation(const float deltaTime, const float timePerFrame, const int imageNumber, const bool linear, IntRect* images)
{
	timeCounter += deltaTime;

	if (timeCounter >= timePerFrame)
	{
		timeCounter -= timePerFrame;

		if (++currentImage == imageNumber)
		{
			if (linear) currentImage = imageNumber - 1;
			else currentImage = 0;
		}

		setTextureRect(images[currentImage]);
	}
}

void Demon::setAnimationState(AnimationState animationState)
{
	if (this->animationState != animationState)
	{
		this->animationState = animationState;
		timeCounter = 0.0f;
		currentImage = 0;
	}
}

void Demon::spawn()
{
	activate();
	setPosition(610, -100);
}

void Demon::notify(Subject* subject)
{
	
}
