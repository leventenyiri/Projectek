#pragma once
class Vector
{
protected:


	double xCoord;
	double yCoord;

public:

	Vector(double xCoord = 0, double yCoord = 0)
	{
		setXCoord(xCoord);
		setYCoord(yCoord);
	}

	void setXCoord(double xCoord)
	{
		if (xCoord > -9999 && xCoord < 9999)
			this->xCoord = xCoord;
	}

	void setYCoord(double yCoord)
	{
		if (yCoord > -9999 && yCoord < 9999)
			this->yCoord = yCoord;
	}

	double getXCoord()const { return xCoord; }
	double getYCoord()const { return yCoord; }
};

