#include "Velocity.h"

Velocity::Velocity(double xCoord,double yCoord,string direction, double speed)
{
	//Ez tulajdonképp egy nagy switch-case csak nem volt kedvem switchelni szóval if else-ztem
	//Azért kell, hogy az irányt be lehessen állítani stringgel, ne kelljen koordinátákkal bajlódni
	startingCoords.setXCoord(xCoord);
	startingCoords.setYCoord(yCoord);
	if ((direction==("NORTH")))
	{
		setDirectionCoords(0, 1);
	}
	else if ((direction==("EAST")))
	{
		setDirectionCoords(1, 0);
	}
	else if ((direction==("SOUTH")))
	{
		setDirectionCoords(0, -1);
	}
	else if ((direction==("WEST")))
	{
		setDirectionCoords(-1, 0);
	}
	else if ((direction==("NORTH-WEST")))
	{
		setDirectionCoords(-1, 1);
	}
	else if ((direction==("NORTH-EAST")))
	{
		setDirectionCoords(1, 1);
	}
	else if ((direction==("SOUTH-EAST")))
	{
		setDirectionCoords(1, -1);
	}
	else if ((direction==("SOUTH-WEST")))
	{
		setDirectionCoords(-1, -1);
	}
	else
	{
		setDirectionCoords(0, 0);
	}
	
	setSpeed(speed);
}
