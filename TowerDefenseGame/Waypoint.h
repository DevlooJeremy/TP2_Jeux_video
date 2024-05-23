#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Waypoint :public Sprite
{
public:
	Waypoint();
	~Waypoint();
	Waypoint* getNext() const;
	void setNext(Waypoint* nextWaypoint);

private:

	Waypoint* nextWaypoint = nullptr;

};

