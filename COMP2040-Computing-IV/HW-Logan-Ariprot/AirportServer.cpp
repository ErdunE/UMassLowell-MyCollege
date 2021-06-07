#include <iostream>
#include <thread>
#include <condition_variable>

#include "AirportServer.h"


/**
*  Called by an Airplane when it wishes to land on a runway
*/
void AirportServer::reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Acquire runway(s)
	{  // Begin critical region


		//unique_lock<mutex> runwaysLock(runwaysMutex);
		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is acquiring any needed runway(s) for landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}

		/**
		 *  ***** Add your synchronization here! *****
		 */

        {
            unique_lock<mutex> lck(requestMutex);
            while (AirportRunways::getNumLandingRequests() == AirportRunways::MAX_LANDING_REQUESTS) {
                cv.wait(lck);
            }
            AirportRunways::incNumLandingRequests();
        }

        {
            unique_lock<mutex> lock1(lockMutex);
            switch (runway) {
                case AirportRunways::RUNWAY_9:
                    lock(mutex9, mutex9and4R, mutex9and15R);
                    break;
                case AirportRunways::RUNWAY_4L:
                    lock(mutex4L, mutex15Rand4L, mutex15Land4L);
                    break;
                case AirportRunways::RUNWAY_4R:
                    lock(mutex4R, mutex9and4R, mutex15Land4R,mutex15Rand4R);
                    break;
                case AirportRunways::RUNWAY_14:
                    mutex14.lock();
                    break;
                case AirportRunways::RUNWAY_15L:
                    lock(mutex15L, mutex15Land4L, mutex15Land4R);
                    break;
                case AirportRunways::RUNWAY_15R:
                    lock(mutex15R, mutex15Rand4R, mutex15Rand4L,mutex9and15R);
                    break;
            }
        }


		// Check status of the airport for any rule violations
        {
            unique_lock<mutex> lck(unlockMutex);
            AirportRunways::checkAirportStatus(runway);
        }
        {
            lock_guard<mutex> lck11(requestMutex);
            AirportRunways::decNumLandingRequests();
            cv.notify_all();
        }
		//runwaysLock.unlock();

	} // End critical region


	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Taxi for a random number of milliseconds
	std::uniform_int_distribution<int> taxiTimeDistribution(1, MAX_TAXI_TIME);
	int taxiTime = taxiTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is taxiing on Runway " << AirportRunways::runwayName(runway)
			 << " for " << taxiTime << " milliseconds\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(taxiTime));

} // end AirportServer::reserveRunway()


 /**
  *  Called by an Airplane when it is finished landing
  */
void AirportServer::releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Release the landing runway and any other needed runways
	{ // Begin critical region

		//unique_lock<mutex> runwaysLock(runwaysMutex);


		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is releasing any needed runway(s) after landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}

		/**
		*  ***** Add your synchronization here! *****
		*/

        {
            lock_guard<mutex> lck1(unlockMutex);
            switch (runway) {
                case AirportRunways::RUNWAY_9:
                    mutex9.unlock();
                    mutex9and4R.unlock();
                    mutex9and15R.unlock();
                    break;
                case AirportRunways::RUNWAY_4L:
                    mutex4L.unlock();
                    mutex15Land4L.unlock();
                    mutex15Rand4L.unlock();
                    break;
                case AirportRunways::RUNWAY_4R:
                    mutex4R.unlock();
                    mutex9and4R.unlock();
                    mutex15Land4R.unlock();
                    mutex15Rand4R.unlock();
                    break;
                case AirportRunways::RUNWAY_14:
                    mutex14.unlock();
                    break;
                case AirportRunways::RUNWAY_15L:
                    mutex15L.unlock();
                    mutex15Land4L.unlock();
                    mutex15Land4R.unlock();
                    break;
                case AirportRunways::RUNWAY_15R:
                    mutex15R.unlock();
                    mutex15Rand4R.unlock();
                    mutex15Rand4L.unlock();
                    mutex9and15R.unlock();
                    break;
            }

            {
                lock_guard<mutex> lck(AirportRunways::checkMutex);
                // Update the status of the airport to indicate that the landing is complete
                AirportRunways::finishedWithRunway(runway);
            }
        }


		//runwaysLock.unlock();

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Wait for a random number of milliseconds before requesting the next landing for this Airplane
	std::uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
	int waitTime = waitTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is waiting for " << waitTime << " milliseconds before landing again\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

} // end AirportServer::releaseRunway()
