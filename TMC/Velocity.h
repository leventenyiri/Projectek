#pragma once
#include "Vector.h"
#include "iostream"
#include "string.h"

using namespace std;

class Velocity : public Vector
{


	double speed;
	Vector startingCoords;
	Vector directionCoords;
	//ide talán directionCoords

public:



	Velocity(double xCoord=0,double yCoord=0,string direction ="NOTHING", double speed = 0);

	void setSpeed(double speed)
	{
		if (speed >= 0 && speed <= 130)
			this->speed = speed;
	}

	void setStartingCoords(double xCoord, double yCoord)
	{
		startingCoords.setXCoord(xCoord);
		startingCoords.setYCoord(yCoord);
	}

	void setDirectionCoords(double xCoord, double yCoord)
	{
		directionCoords.setXCoord(xCoord);
		directionCoords.setYCoord(yCoord);
	}

	double getStartingCoordsX() const { return startingCoords.getXCoord(); }
	double getStartingCoordsY() const { return startingCoords.getYCoord(); }
	double getDirectionCoordsX() const { return directionCoords.getXCoord(); }
	double getDirectionCoordsY() const { return directionCoords.getYCoord(); }


	double getSpeed() { return speed; }
};



