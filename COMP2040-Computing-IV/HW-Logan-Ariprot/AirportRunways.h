/**
*  Class AirportRunways provides definitions of constants and helper methods for the Airport simulation.
*/

#ifndef AIRPORT_RUNWAYS_H
#define AIRPORT_RUNWAYS_H

#include <iostream>
#include <string>
#include <mutex>

using namespace std;


class AirportRunways
{
public:

	static const int NUM_RUNWAYS = 6;     // Number of runways in this simulation
	static const int NUM_AIRPLANES = 7;   // Number of airplanes in this simulation
	static const int MAX_LANDING_REQUESTS = 6; // Maximum number of simultaneous landing requests that Air Traffic Control can handle

	enum RunwayNumber { RUNWAY_4L, RUNWAY_4R, RUNWAY_9, RUNWAY_14, RUNWAY_15L, RUNWAY_15R };

	static mutex checkMutex; // enforce mutual exclusion on checkAirportStatus

	static string runwayName(RunwayNumber rn);

	/**
	*  Check the status of the aiport with respect to any violation of the rules.
	*/
	static void checkAirportStatus(RunwayNumber requestedRunway);

	/**
	*  requestRunway() and finishedWithRunway() are helper methods for keeping track of the airport status
	*/

	static void requestRunway(RunwayNumber rn)
	{
		runwayInUse[rn]++;

	} // end useRunway()


	static void finishedWithRunway(RunwayNumber rn)
	{
		runwayInUse[rn]--;

	} // end finishedWithRunway()


	static int getNumLandingRequests()
	{
		return numLandingRequests;
	}


	static void incNumLandingRequests()
	{
		numLandingRequests++;
		if (numLandingRequests > maxNumLandingRequests)
			maxNumLandingRequests = numLandingRequests;
	}


	static void decNumLandingRequests()
	{
		numLandingRequests--;
	}

private:

	/**
	 *  The following variables and methods are used to detect violations of the rules of this simulation.
	 */

	static int runwayInUse[NUM_RUNWAYS]; // Keeps track of how many airplanes are attempting to land on a given runway

	static int numLandingRequests; // Keeps track of the number of simultaneous landing requests

	static int maxNumLandingRequests; // Keeps track of the max number of simultaneous landing requests

}; // end class AirportRunways

#endif

