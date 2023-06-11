#include "Moving_Station.h"

void Moving_Station::actualPositon() //itt a 100-as osztó csak azért mert különben nagyon messzi koordináták lennének...
{ 
   velocity.setStartingCoords((velocity.getStartingCoordsX() + (velocity.getSpeed()/100)* velocity.getDirectionCoordsX()*(time.convertToSec()-timestamp.convertToSec())), (velocity.getStartingCoordsY() + (velocity.getSpeed()/100) * velocity.getDirectionCoordsY()* (time.convertToSec() - timestamp.convertToSec())));
   Moving_Station::setTimestamp(time); 
   //az adott irányba veszem a sebességet és az idõ elteltével megnézem mennyit mozog, majd a kiindulásihoz hozzáadom

   //egy változóban rögzítem az idõt amikor legutóbb meg lett hívva, és legközelebb abból kivonom az idõt 
   //amivel megszorzom különben olyan hiba lenne, hogy ha többedjére hívnám meg, akkor a beállított helyzetet venné,
   //és azt szorozná a kezdet óta eltelt idõvel
}

double Moving_Station::averageSpeed(const Vehicles& p)
{
    double sum = 0;
    int n = 0;
    actualPositon(); //fontos, hogy a pillanatnyi tartózkodási helyénél nézzem

    for (int i = 0; i < p.getElementNum(); i++)
        if (sqrt((velocity.getStartingCoordsX() - (p.getP()[i].getPosition().getXCoord())) * (velocity.getStartingCoordsX() - (p.getP()[i].getPosition().getXCoord())) + (velocity.getStartingCoordsY() - (p.getP()[i].getPosition().getYCoord())) * (velocity.getStartingCoordsY() - (p.getP()[i].getPosition().getYCoord()))) <= range)
        {
            n++;
            sum += p.getP()[i].getSpeed();
        }
    //itt azt nézem meg, hogy az adott jármû bele esik-e az állomás hatótávjába sqrt((x1-x2)^2+(y1-y2)^2)
    //mivel csak azokat fogom figyelembe venni az adott toronynál

    return (sum / (double)n);

}

string Moving_Station::teszt_randomolo()
{
    int a = 0;
    a = rand() % 8;
    if (a == 0)
        return "NORTH";
    if (a == 1)
        return "EAST";
    if (a == 2)
        return "SOUTH";
    if (a == 3)
        return "WEST";
    if (a == 4)
        return "NORTH-WEST";
    if (a == 5)
        return "NORTH-EAST";
    if (a == 6)
        return "SOUTH-EAST";
    if (a == 7)
        return "SOUTH-WEST";
    else return
        "Mi_tortent?";
}


Station** Moving_Station::initStations(Station** tomb, int n)
{
    if (n > 100)
        return nullptr;
    int i = 0;

    for (i = 0; i < n; i++)
    {
        tomb[i] = new Station(rand() % 500, randCoord(), randCoord(), rand() % 130 + 50);
    }

    Time t(0, 0, 0);



    for (; i < 100; i++)
    {
        Velocity Q(randCoord(), randCoord(), teszt_randomolo(), rand() % 130);
        tomb[i] = new Moving_Station(Q, t, rand() % 500, rand() % 130 + 50);
    }

    return tomb;
}



Time Moving_Station::time = 0;
