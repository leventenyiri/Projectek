#pragma once
#include "math.h"
#include "Vector.h"
#include <cstdlib>
class Vehicle
{
	double speed;
	Vector position;

public:

	Vehicle(double speed , Vector& position)
	{
		this->speed = speed;
		this->position.setXCoord(position.getXCoord());
		this->position.setYCoord(position.getYCoord());
	}
	
	Vehicle()
	{
		this->speed = 0;
		this->position.setXCoord(0);
		this->position.setYCoord(0);
	}

	void setSpeed(double speed) 
	{
		if (speed >= 0 && speed <= 130)
		this->speed = speed;
	}

	double getSpeed() { return speed; }
	Vector getPosition() { return position; }
	void setPosition(double a, double b)
	{
		position.setXCoord(a);
		position.setYCoord(b);
	}

	double randCoord()
	{
		if (fabs((rand() % 2) - 1))
			return rand() % 1000;
		return -(rand() % 1000);
	}

};

