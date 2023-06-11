#pragma once
#include "Station.h"
#include "Velocity.h"
#include "Time.h"

class Moving_Station : public Station
{

	Velocity velocity;
	static Time time;
	Time timestamp;

public:

	Moving_Station(const Velocity& velocity=0, const Time& timestamp=0, double range = 0, int speedLimit = 0)
	{
		setRange(range);
		position.setXCoord(velocity.getStartingCoordsX());
		position.setYCoord(velocity.getStartingCoordsY());
		setVelocity(velocity);
		setSpeedLimit(speedLimit);
		setTimestamp(timestamp);
	}

	Velocity getVelocity() { return velocity; }
	Time getTime() { return time; }

	void setVelocity(const Velocity& V)
	{
		if ((-1 <= (V.getXCoord() && V.getYCoord()) <= 1))  //speedet nem kell ellenõrizni, ott a setter megcsinálja, itt ez 
			velocity = V;									//egy kicsit más, nem akartam erre egy külön settert
			
	}

	static void setTime(unsigned hour, unsigned min, unsigned sec)
	{
		time.setHour(hour);
		time.setMin(min);
		time.setSec(sec);
	}

	void setTimestamp(const Time& time)
	{
		timestamp.setHour(time.getHour());
		timestamp.setMin(time.getMin());
		timestamp.setSec(time.getSec());
	}


	void actualPositon();
	double averageSpeed(const Vehicles& p);
	string type() { return "Moving_Station"; }

	//Ezek csak a teszteléshez random adatokkal feltöltenek nekem állomásokat

	double randCoord()
	{
		if (fabs((rand() % 2) - 1))
			return rand() % 1000;
		return -(rand() % 1000);
	}

	string teszt_randomolo(); 
	
	Station** initStations(Station** tomb, int n);

};





