#pragma once
#include "GameObject.h"
#include "IObserver.h"
#include "Subject.h"

class TowerEmplacement : public GameObject, public IObserver, public Subject
{
public:
	TowerEmplacement();
	void init(const Vector2f& position);
	void notify(Subject* subject);

private:
	bool mouseInBound(const Vector2f mousePosition) const;
};

