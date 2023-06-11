#include "Velocity.h"

Velocity::Velocity(double xCoord,double yCoord,string direction, double speed)
{
	//Ez tulajdonk�pp egy nagy switch-case csak nem volt kedvem switchelni sz�val if else-ztem
	//Az�rt kell, hogy az ir�nyt be lehessen �ll�tani stringgel, ne kelljen koordin�t�kkal bajl�dni
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
