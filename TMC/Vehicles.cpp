#include "Vehicles.h"

Vehicles::Vehicles(unsigned elementNum)
{
	this->elementNum = elementNum;
	p = new Vehicle[elementNum];
}

Vehicles::Vehicles(const Vehicles& other)
{
	elementNum = other.elementNum;
	p = nullptr;
	p = new Vehicle[elementNum];
	p = other.p;
}
