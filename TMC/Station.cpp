#include "Station.h"

string Station::severityOfJam(double average)
{
    double tmp = average / speedLimit;
    if (tmp <= 0.25)
        return "Nagyon durva";
    else if (tmp > 0.25 && tmp <= 0.5)
        return "Durva";
    else if (tmp > 0.5 && tmp < 0.75)
        return "Enyhe";
    else if (tmp > 0.75 && tmp != 0)
        return "Nincs dugo :)";
    else
        return "Nincs jarmu hatotavon belul";
}


double Station::averageSpeed(const Vehicles& p)
{
    double sum = 0;
    int n = 0;

    for (int i = 0; i < p.getElementNum(); i++)
        if (sqrt((position.getXCoord() - (p.getP()[i].getPosition().getXCoord())) * (position.getXCoord() - (p.getP()[i].getPosition().getXCoord())) + (position.getYCoord() - (p.getP()[i].getPosition().getYCoord())) * (position.getYCoord() - (p.getP()[i].getPosition().getYCoord()))) <= range)
        {
            n++;
            sum += p.getP()[i].getSpeed();
        }
    //itt azt nézem meg, hogy az adott jármû bele esik-e az állomás hatótávjába sqrt((x1-x2)^2+(y1-y2)^2)
    //mivel csak azokat fogom figyelembe venni az adott toronynál

    return (sum / (double)n);
}