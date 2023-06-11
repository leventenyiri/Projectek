#include "Station.h"
#include "Moving_Station.h"
#include "Vehicle.h"
#include "Vehicles.h"
#include <cstdlib>
#include <iostream>
#include <ios>


using namespace std;

int main()
{
	srand(time(0));
	Vehicles a(100);
	Station A(80, 5, 5, 80); //range,x,y,speedlimit
	Velocity X(5,10,"NORTH", 40); //x,y,dir,speed
	Velocity Z(10, 15, "SOUTH", 75);
	Time timestamp(0,0,0);
	Moving_Station B(X,timestamp, 5000, 70); //velocity,timestamp,range,speedlimit


	for (int i = 0; i < 100; i++) //itt feltöltöm a vehicles tömbömet random értékekkel, ezt késõbb több tesztnél használom
	{
		a.getP()[i].setSpeed(rand() % 130);
		a.getP()[i].setPosition(a.getP()[i].randCoord(), a.getP()[i].randCoord());
	}


//TESZT 1: mozgó állomás helyzetének változása

	/*

	cout << B.getVelocity().getStartingCoordsX() << endl;
	cout << B.getVelocity().getStartingCoordsY() << endl;

	B.setTime(3, 23, 22);

	B.actualPositon(); 

	cout << B.getVelocity().getStartingCoordsX() << endl;
	cout << B.getVelocity().getStartingCoordsY()<< endl;
	cout << endl;

	*/
	

	//a jármûvek adóvevõn keresztül elküldik az állomásoknak a helyzetüket és sebességüket

// TESZT 2: álló és mozgó állomások környezetében dugó vizsgálata

	/*

	Moving_Station::setTime(2,50,12); 

	cout << A.severityOfJam(A.averageSpeed(a)) <<endl; 
	cout << B.severityOfJam(B.averageSpeed(a)) << endl;
	cout << endl;

	//itt a távolságot figyelembe véve random értékekbõl generált jármûvekkel megadja a dugó súlyosságát
	
	*/

//TESZT 3: heterogén kollekció

	/*
	
	Moving_Station C(Z, timestamp, 45, 130);

	cout << B.severityOfJam(B.averageSpeed(a))<<endl;
	cout << C.severityOfJam(C.averageSpeed(a))<<endl;
	cout << endl;

	Station* teszt[2];
	Moving_Station* o = &B;
	Moving_Station* l = &C;
	teszt[0] = o;
	teszt[1] = l;

	cout << teszt[0]->severityOfJam(static_cast<Moving_Station*>(teszt[0])->averageSpeed(a)) << endl; 
	cout << teszt[1]->severityOfJam(static_cast<Moving_Station*>(teszt[1])->averageSpeed(a)) << endl;
	
	*/


//Alkalmazás: heterogén kollekció sok adattal, tetszõleges helyen dugó lekérdezése
	
	
	
	
	Station* stations[100] = { 0 }; //pointerekkel kell feltolteni

	Moving_Station* p=nullptr;

	p->initStations(stations, 30); //ez most x db station-nel és 100-x db moving stationnel tölti fel

	int hour = 0, min = 0, sec = 0;

	cout << "Adjon meg idot(ora, perc, masodperc):"<<endl;
	cin>>hour>>min>>sec;

	if (((hour<0) || min<0 || sec<0) || (hour > 24) || (min>60) || (sec>60))
		cin.setstate(ios::failbit);

	if (cin.fail())
	{
		for (int i = 0; i < 100; i++)
			delete[] stations[i];

		return -1;
	}
	Time(hour, min, sec);

	int n = 0;

	for (int i = 0; i < 100; i++)
	{
		
		if (stations[i]->type() == "Station")
		{
			cout << "A(z)" << i+1 << "-es szamu allomasnal: " << stations[i]->severityOfJam(stations[i]->averageSpeed(a)) << endl;
			n++;
		}
		else
		{
			p = static_cast<Moving_Station*>(stations[i]);
			cout <<"A(z)"<<i-n+1<<"-es szamu mozgo allomasnal: "<< p->severityOfJam(p->averageSpeed(a)) << endl;
		}
		cout << endl;
	}



	cout << "Adjon meg idot(ora, perc, masodperc):" << endl;
	cin >> hour >> min >> sec;
	if (((hour < 0) || min < 0 || sec < 0) || (hour > 24) || (min > 60) || (sec > 60))
		cin.setstate(ios::failbit);

	if (cin.fail())
	{
		for (int i = 0; i < 100; i++)
			delete[] stations[i];

		return -1;
	}
	Time(hour, min, sec);
	for (int i = 0; i < 100; i++)
	{
		if (stations[i]->type() == "Moving_Station")
			static_cast<Moving_Station*>(stations[i])->actualPositon();
	}

	double aparam, bparam;
	cout << "Adjon meg egy x es egy y koordinatat:" << endl;
	cin >> aparam >> bparam;

	if ((((aparam <-9999) || (bparam < -9999))) || ((aparam>9999) || (bparam >9999)))
		cin.setstate(ios::failbit);

	if (cin.fail())
	{
		for (int i = 0; i < 100; i++)
			delete[] stations[i];

		return -1;
	}
	Vector(aparam, bparam);
	int k = 0;
	
	for (int i = 0; i < 100; i++)
	{
		double distance = sqrt(pow((aparam - stations[i]->getPosition().getXCoord()), 2) + pow(bparam - stations[i]->getPosition().getYCoord(), 2));
		if (stations[i]->getRange() >= (distance))
		{//Megnézem a kapott koordináták és az állomások távolságát és az elsõ olyannál, amelyiknél kisebb== a távolságuk a hatótávjával, ott megnézem, hogy milyen a dugó
			cout << endl;
			cout<<"A ("<<aparam<<' '<<','<<' '<<bparam<< ")pozicioban a dugo: " <<stations[i]->severityOfJam(stations[i]->averageSpeed(a))<<endl;
			k++;
		}

		if (k != 0)
			break;
	}

	if (k == 0)
		cout << "Nincs allomas hatotavolsagban" << endl;

	for(int i=0;i<100;i++)
	delete[] stations[i];

	
	
	return 0;
}