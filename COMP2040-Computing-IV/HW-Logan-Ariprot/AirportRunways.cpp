#include "AirportRunways.h"

int AirportRunways::runwayInUse[AirportRunways::NUM_RUNWAYS];

int AirportRunways::numLandingRequests = 0;

int AirportRunways::maxNumLandingRequests = 0;

mutex AirportRunways::checkMutex;


string AirportRunways::runwayName(RunwayNumber rn)
{
	switch (rn)
	{
	case RUNWAY_4L:
		return "4L";
	case RUNWAY_4R:
		return "4R";
	case RUNWAY_9:
		return "9";
	case RUNWAY_14:
		return "14";
	case RUNWAY_15L:
		return "15L";
	case RUNWAY_15R:
		return "15R";
	default:
		return "Unknown runway " + rn;
	} // end switch

} // end AirportRunways::runwayName()


 /**
  *  Check the status of the aiport with respect to any violation of the rules.
  */
void AirportRunways::checkAirportStatus(RunwayNumber requestedRunway)
{
	lock_guard<mutex> checkLock(checkMutex);

	bool crash = false; // Set to true if any rule is violated

	cout << "\nChecking airport status for requested Runway " << runwayName(requestedRunway) << "..." << endl;

	requestRunway(requestedRunway);

	// Check the number of landing requests
	cout << "Number of simultaneous landing requests == " << numLandingRequests
		 << ", max == " << maxNumLandingRequests << endl;

	if (numLandingRequests > MAX_LANDING_REQUESTS)
	{
		cout << "***** The number of simultaneous landing requests exceeds Air Traffic Control limit of " << MAX_LANDING_REQUESTS << "!\n";
		crash = true;
	}

	// Check the occupancy of each runway
	for (int i = RUNWAY_4L; i <= RUNWAY_15R; i++)
	{
		cout << "Number of planes landing on runway " << runwayName(RunwayNumber(i)) << " == " << runwayInUse[i] << endl;
		
		if (runwayInUse[i] > 1)
		{
			cout << "***** The number of planes landing on runway " << runwayName(RunwayNumber(i)) << " is greater than 1!\n";
			crash = true;
		}
	}

	// Check individual restrictions on each runway
	if ((runwayInUse[RUNWAY_9] > 0)
		&& ((runwayInUse[RUNWAY_4R] > 0) || (runwayInUse[RUNWAY_15R] > 0)))
	{
		cout << "***** Runways 9, 4R, and/or 15R may not be used simultaneously!\n";
		crash = true;
	}

	if (((runwayInUse[RUNWAY_15L] > 0) || (runwayInUse[RUNWAY_15R] > 0))
		&& ((runwayInUse[RUNWAY_4L] > 0) || (runwayInUse[RUNWAY_4R] > 0)))
	{
		cout << "***** Runways 15L or 15R may not be used simultaneously with Runways 4L or 4R!\n";
		crash = true;
	}

	// If any of the rules have been violated, terminate the simulation
	if (crash)
	{
		cout << "***** CRASH! One or more rules have been violated. Due to the crash, the airport is closed!\n";
		exit(-1); // Abnormal program termination
	}

	// Status check is normal
	cout << "Status check complete, no rule violations (yay!)\n";

} // end AirportRunways::checkAirportStatus()
