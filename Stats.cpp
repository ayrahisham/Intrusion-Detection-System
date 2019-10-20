// NUR SUHAIRA BTE BADRUL HISHAM 5841549
// HUNG SIEW KEE		 5986606
// JANICE LIM JIA HWEI		 5987040
// Assignment 3
// Email System Event Modeller & Intrusion Detection System
// Stats.cpp
#include "Stats.h"

Stats::Stats ()
{
	strcpy (this->eventName, "");
	this->mean = 0.0;
	this->stddev = 0.0;	
	this->sum = 0.0;
	this->variance = 0.0;
}

Stats::~Stats ()
{

}

Stats::Stats (char* eventName, float mean, float stddev)
{
	strcpy (this->eventName, eventName);
	this->mean = mean;
	this->stddev = stddev;	
	this->sum = 0.0;
	this->variance = 0.0;
}

char* Stats::getEventName ()
{
	return eventName;
}

float Stats::getMean ()
{
	return mean;
}

float Stats::getStddev ()
{
	return stddev;
}

float Stats::getSum ()
{
	return sum;
}

float Stats::getVariance ()
{
	return variance;
}

void Stats::setEventName (string eventName)
{
	strcpy (this->eventName, eventName.c_str());
}

void Stats::setMean (float mean)
{
	this->mean = mean;
}

void Stats::setStddev (float stddev)
{
	this->stddev = stddev;
}

void Stats::setSum (float sum)
{
	this->sum = sum;
}

void Stats::setVariance (float variance)
{
	this->variance = variance;
}
