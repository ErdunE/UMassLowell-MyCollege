/**
*  Airplane.h
*  Definition of the Airplane class
*/

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "AirportRunways.h"
#include "AirportServer.h"


class Airplane
{
public:

	int airplaneNum;
	AirportServer* apServ;

	// Value constructor for the Airplane class
	Airplane(int num, AirportServer* s)
	{
		airplaneNum = num;
		apServ = s;
	}


	// Setter method for requestedRunway
	void setRequestedRunway(AirportRunways::RunwayNumber runway)
	{
		requestedRunway = runway;
	}


	// The run() function for Airplane threads in Airport will call this function
	void land();


private:

	AirportRunways::RunwayNumber requestedRunway; // Picked at random

}; // end class Airplane

#endif

