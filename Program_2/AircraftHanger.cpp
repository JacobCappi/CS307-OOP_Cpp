#include "AircraftHanger.h"


AircraftHanger::AircraftHanger(){
}
AircraftHanger::~AircraftHanger(){
}

AircraftHanger *AircraftHanger::getInstance(){
	static AircraftHanger *instance = NULL;
	if(instance == NULL)
	{
		instance = new AircraftHanger();
	}
	return instance;
}

void AircraftHanger::init(char* fileName){
	// Had to pass in fileName as fdp is weird and isn't static like it says it is...
    bjF.init(fileName);
    pjF.init(fileName);
    seF.init(fileName);
}

AircraftData* AircraftHanger::getAircraft(char* craftName){
    AircraftData *retVal = NULL;
    // weird logic due to the inability to check flightname to flight make outside of the factories
    // the fdp was written to where it would only be able to go through once
    retVal = bjF.getAircraft(craftName);
    if(!retVal){
        retVal = pjF.getAircraft(craftName);
        if(!retVal){
            retVal = seF.getAircraft(craftName);
        }
    }
    return retVal;

}
