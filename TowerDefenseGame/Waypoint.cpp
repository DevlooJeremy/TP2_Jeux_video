#include "Waypoint.h"
#include "ContentPipeline.h"

Waypoint::Waypoint()
{
	setTexture(ContentPipeline::getInstance().getWaypointTexture());
}

Waypoint::~Waypoint()
{
}

Waypoint* Waypoint::getNext() const
{
	return this->nextWaypoint;
}

void Waypoint::setNext(Waypoint* nextWaypoint)
{
	this->nextWaypoint = nextWaypoint;
}