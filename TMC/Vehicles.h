#pragma once
#include "Vehicle.h"


class Vehicles
{
	Vehicle* p;
	unsigned elementNum;

public:

	Vehicles(unsigned elementNum = 0);
	Vehicles(const Vehicles& other);
	~Vehicles() 
	{
		delete[] p;
	}

	void setElementNum(unsigned elementNum)
	{
		if (elementNum >= 0 && elementNum < 10000)
			this->elementNum = elementNum;
	}

	unsigned getElementNum()const { return elementNum; }
	Vehicle* getP() const { return p; }
};

