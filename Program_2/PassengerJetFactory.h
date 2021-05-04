
#pragma once
#include "AirCraftAbstractFactory.h"


class PassengerJetFactory: public AircraftAbstractFactory{
    private:
        FlightDataParser fdp = *FlightDataParser::getInstance();
        char airMake[32];
        char airType[32];
        double rateClimb;
        double wingspan;
        double length;
        double rateCruise;
        double cruisingAlt;

        PassengerJetFactory();
        // Parser writer obviously had a usage code in mind, but I couldn't figure it out
        // storing as vector and will be returning as an address.
		// Video said just use 1 instance of each plane and pass that in to implement 'flyweight'
        vector<AircraftData> passengerJetFactory; // Uses Flyweight as each class is only referenced once
		// Maybe my implementation is bad, but I always only had one instance of plane that I just 
		// took data from to calculate the print data, so factories just kind of divide that up
    public:
    // virtual get Aircraft() from inheritance;
        AircraftData *getAircraft(char* craftName) override;
        ~PassengerJetFactory();
		static PassengerJetFactory *getInstance();	// Get the singleton instance
        void init(char *fileName); // making this concrete
};
