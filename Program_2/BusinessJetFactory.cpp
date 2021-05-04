#include "BusinessJetFactory.h"

BusinessJetFactory::BusinessJetFactory(){
}

BusinessJetFactory::~BusinessJetFactory(){
}

BusinessJetFactory *BusinessJetFactory::getInstance(){
	static BusinessJetFactory *instance = NULL;
	if(instance == NULL)
	{
		instance = new BusinessJetFactory();
	}
	return instance;
}

void BusinessJetFactory::init(char *fileName){
    AircraftType type = BUSINESSJET;
	fdp.InitFlightData(fileName); // For some reason, singleton design pattern resets fdp instead of static
    while(fdp.getAircraftData(type, airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt)){
        businessJetFactory.push_back(AircraftData(airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt));
    }

}

AircraftData* BusinessJetFactory::getAircraft(char* craftName){
    for(int i = 0; i<businessJetFactory.size(); i++){
        businessJetFactory.at(i).getMake(airMake);
        if(strcmp(airMake, craftName) == 0){
            return &businessJetFactory.at(i);
        }
    }
    return NULL;
}
