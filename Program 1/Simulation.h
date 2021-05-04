#include <iostream>
#include <fstream>
#include <vector>

#include <chrono>
#include <thread>

#include "CityDataParser.h"
#include "FlightDataParser.h"
#include "CityData.h"
#include "AircraftData.h"
#include "FlightData.h"

class Simulation{
    private:
        CityDataParser cdp;
        FlightDataParser fdp;
        int runSpeed;
        int currentHr;
        int currentMin;
        char filename[32];

// ----- City Data Variables
        char cityName[32];
        char cityState[32];
        char citySymbol[32];
        double lat;
        double lon;
        vector<CityData> cityData;

        double distanceResult;
        int index1;
        int index2;
        char **citySymbolArr;
        double *cityDistanceArr;

// ----- END

// ----- Flight Data Variables
        char airMake[32];
        char airType[32];
        double rateClimb;
        double wingspan;
        double length;
        double rateCruise;
        double cruisingAlt;

        vector<AircraftData> aircraftData;

        char airline[32];
        char planeType[32];
        int flightNum;
        char cityDep[4];
        int hour;
        int minute;
        char cityDes[4];
        int depHr;
        int depMin;
        int craftIndex;

        vector<FlightData> flightData;

// ----- END

// ----- END
    public:
        Simulation();
        ~Simulation();
        void init();
// ----- Run Sim Class
        void runSim();

        void fetchAircraftInfo();
        void fetchCityInfo();
        int fetchIndex();
        int fetchDistance();

        void printFlights();
        void printFlightDataDeparting(FlightData &currentFlight);
        void printFlightDataDepart(FlightData &currentFlight);
        void printFlightDataArrival(FlightData &currentFlight);

        void printTime();
        void updateTime();
        void setRunSpeed(int x);

};

