#pragma once
#include "Scene.h"

using namespace sf;

class SceneTransition : public Scene
{
public:
	SceneTransition(RenderWindow& renderWindow, Event& event, int currentWave);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;
	void startWave();

	View view;

	Font font;
	Text message;

	float displayTime;

	const float MAX_DISPLAY_TIME = 3.0f;
};