
#pragma once
#include "BusinessJetFactory.h"
#include "PassengerJetFactory.h"
#include "SingleEngineFactory.h"

// inspired by the pizza shops (?)
class AircraftHanger{
    private:
        BusinessJetFactory bjF = *BusinessJetFactory::getInstance();
        PassengerJetFactory pjF = *PassengerJetFactory::getInstance();
        SingleEngineFactory seF = *SingleEngineFactory::getInstance();

        AircraftHanger();
    public:
        ~AircraftHanger();
		static AircraftHanger *getInstance();	// Get the singleton instance
        void init(char *fileName);

        AircraftData *getAircraft(char* name);

    
};
