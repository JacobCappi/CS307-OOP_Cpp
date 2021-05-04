#include "SingleEngineFactory.h"

SingleEngineFactory::SingleEngineFactory(){
}

SingleEngineFactory::~SingleEngineFactory(){
}

SingleEngineFactory *SingleEngineFactory::getInstance(){
	static SingleEngineFactory *instance = NULL;
	if(instance == NULL)
	{
		instance = new SingleEngineFactory();
	}
	return instance;
}

void SingleEngineFactory::init(char *fileName){
    AircraftType type = SINGLEENGINE;
	fdp.InitFlightData(fileName); // For some reason, singleton design pattern resets fdp instead of static
    while(fdp.getAircraftData(type, airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt)){
        singleEngineFactory.push_back(AircraftData(airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt));
    }

}

AircraftData* SingleEngineFactory::getAircraft(char* craftName){
    for(int i = 0; i<singleEngineFactory.size(); i++){
        singleEngineFactory.at(i).getMake(airMake);
        if(strcmp(airMake, craftName) == 0){
            return &singleEngineFactory.at(i);
        }
    }
    return NULL;
}
