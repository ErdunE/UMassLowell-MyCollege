#include <random>
#include <thread>
#include <chrono>

#include "Airplane.h"

// The run() function in Airport will call this function
void Airplane::land()
{
	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> runwayNumberDistribution(AirportRunways::RUNWAY_4L, AirportRunways::RUNWAY_15R);

	while (true)
	{
		// Get ready to land
		requestedRunway = AirportRunways::RunwayNumber(runwayNumberDistribution(generator));

		apServ->reserveRunway(airplaneNum, requestedRunway);

		// Landing complete
		apServ->releaseRunway(airplaneNum, requestedRunway);

		// Wait on the ground for a while (to prevent starvation of other airplanes)
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	} // end while

} // end Airplane::land
