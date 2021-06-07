/**
*  AirportServer.h
*  This class defines the methods called by the Airplanes
*/

#ifndef AIRPORT_SERVER_H
#define AIRPORT_SERVER_H

#include <mutex>
#include <random>
#include <condition_variable>

#include "AirportRunways.h"



class AirportServer
{
public:

	/**
	*  Default constructor for AirportServer class
	*/
	AirportServer()
	{
		// ***** Initialize any Locks and/or Condition Variables here as necessary *****

	} // end AirportServer default constructor


	  /**
	  *  Called by an Airplane when it wishes to land on a runway
	  */
    void reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway);

	/**
	*  Called by an Airplane when it is finished landing
	*/
	void releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway);


private:

	// Constants and Random number generator for use in Thread sleep calls
	static const int MAX_TAXI_TIME = 10; // Maximum time the airplane will occupy the requested runway after landing, in milliseconds
	static const int MAX_WAIT_TIME = 100; // Maximum time between landings, in milliseconds

	/**
	*  Declarations of mutexes and condition variables
	*/
	mutex runwaysMutex; // Used to enforce mutual exclusion for acquiring & releasing runways

	/**
	 *  ***** Add declarations of your own Locks and Condition Variables here *****
	 */
	 mutex lockMutex;
	 mutex unlockMutex;
	 mutex mutex9and4R, mutex9and15R, mutex15Land4L, mutex15Rand4L, mutex15Land4R, mutex15Rand4R;
	 mutex mutex9;
	 mutex mutex4R, mutex15R, mutex4L;
	 mutex mutex15L;
	 mutex mutex14;
	 mutex requestMutex;
	 condition_variable cv;

}; // end class AirportServer

#endif
