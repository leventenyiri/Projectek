#include "Moving_Station.h"

void Moving_Station::actualPositon() //itt a 100-as oszt� csak az�rt mert k�l�nben nagyon messzi koordin�t�k lenn�nek...
{ 
   velocity.setStartingCoords((velocity.getStartingCoordsX() + (velocity.getSpeed()/100)* velocity.getDirectionCoordsX()*(time.convertToSec()-timestamp.convertToSec())), (velocity.getStartingCoordsY() + (velocity.getSpeed()/100) * velocity.getDirectionCoordsY()* (time.convertToSec() - timestamp.convertToSec())));
   Moving_Station::setTimestamp(time); 
   //az adott ir�nyba veszem a sebess�get �s az id� eltelt�vel megn�zem mennyit mozog, majd a kiindul�sihoz hozz�adom

   //egy v�ltoz�ban r�gz�tem az id�t amikor legut�bb meg lett h�vva, �s legk�zelebb abb�l kivonom az id�t 
   //amivel megszorzom k�l�nben olyan hiba lenne, hogy ha t�bbedj�re h�vn�m meg, akkor a be�ll�tott helyzetet venn�,
   //�s azt szorozn� a kezdet �ta eltelt id�vel
}

double Moving_Station::averageSpeed(const Vehicles& p)
{
    double sum = 0;
    int n = 0;
    actualPositon(); //fontos, hogy a pillanatnyi tart�zkod�si hely�n�l n�zzem

    for (int i = 0; i < p.getElementNum(); i++)
        if (sqrt((velocity.getStartingCoordsX() - (p.getP()[i].getPosition().getXCoord())) * (velocity.getStartingCoordsX() - (p.getP()[i].getPosition().getXCoord())) + (velocity.getStartingCoordsY() - (p.getP()[i].getPosition().getYCoord())) * (velocity.getStartingCoordsY() - (p.getP()[i].getPosition().getYCoord()))) <= range)
        {
            n++;
            sum += p.getP()[i].getSpeed();
        }
    //itt azt n�zem meg, hogy az adott j�rm� bele esik-e az �llom�s hat�t�vj�ba sqrt((x1-x2)^2+(y1-y2)^2)
    //mivel csak azokat fogom figyelembe venni az adott toronyn�l

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
