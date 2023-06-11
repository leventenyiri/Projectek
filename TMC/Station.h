#pragma once
#include "iostream"
#include "Vehicle.h"
#include "Vehicles.h"
#include "Vector.h"

using namespace std;

class Station
{
protected:

	Vector position; // állomas helye
	double range; //km
	int speedLimit;

public:


	Station(double range = 0, double xCoord = 0, double yCoord = 0, int speedLimit = 0)
	{
		setRange(range);
		position.setXCoord(xCoord);
		position.setYCoord(yCoord);
		setSpeedLimit(speedLimit);
	}

	Station(const Station& other)
	{
		setRange(other.range);
		position.setXCoord(other.position.getXCoord());
		position.setYCoord(other.position.getYCoord());
		setSpeedLimit(other.speedLimit);
	}

	void setRange(double range)
	{
		if (range >= 0 && range < 500000000)
			this->range = range;
	}

	void setSpeedLimit(int speedLimit)
	{
		if (speedLimit > 0 && speedLimit <= 130)
			this->speedLimit = speedLimit;
	}

	double getRange() { return range; }
	double getSpeedLimit() { return speedLimit; }
	Vector getPosition() { return position; }
	double averageSpeed(const Vehicles& p);
	string severityOfJam(double average);
	virtual string type() { return "Station"; }

};


