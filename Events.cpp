#include "Events.h"

Events::Events ()
{
	strcpy (this->eventName, "");
	this->type = 'C';
	this->min = 0;
	this->max = 0;
	if (weight > 0)
	{
		this->weight = weight;
	}
	else
	{
		this->weight = 0;
	}
}

Events::~Events ()
{

}

Events::Events (char* eventName, char type, float min, float max, int weight)
{
	strcpy (this->eventName, eventName);
	this->type = type;
	this->min = min;
	this->max = max;
	if (weight > 0)
	{
		this->weight = weight;
	}
	else
	{
		this->weight = 0;
	}
}
		
char* Events::getEventName ()
{
	return eventName;
}

char Events::getType ()
{
	return type;
}

float Events::getMin ()
{
	return min;
}
		
float Events::getMax ()
{
	return max;
}

int Events::getWeight ()
{
	return weight;
}

void Events::setEventName (string eventName)
{
	strcpy (this->eventName, eventName.c_str());
}

void Events::setType (char type)
{
	this->type = type;
}

void Events::setMin (float min)
{
	this->min = min;
}

void Events::setMax (float max)
{
	this->max = max;
}

void Events::setWeight (int weight)
{
	this->weight = weight;
}
