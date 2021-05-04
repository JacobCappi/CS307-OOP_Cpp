#pragma once

#include "AircraftData.h"
#include "AircraftTypes.h"
#include "FlightDataParser.h"
#include <cstring>
#include <vector>

// No proper definitions as this is just an interface
class AircraftAbstractFactory{
    private:
    public:
        AircraftAbstractFactory();
        virtual ~AircraftAbstractFactory(); // some issue with vtable?
        virtual AircraftData *getAircraft(char* craftName){ return NULL;}

};

