#include "PassengerJetFactory.h"

PassengerJetFactory::PassengerJetFactory(){
}

PassengerJetFactory::~PassengerJetFactory(){
}

PassengerJetFactory *PassengerJetFactory::getInstance(){
	static PassengerJetFactory *instance = NULL;
	if(instance == NULL)
	{
		instance = new PassengerJetFactory();
	}
	return instance;
}

void PassengerJetFactory::init(char *fileName){
    AircraftType type = PASSENGERJET;
	fdp.InitFlightData(fileName); // For some reason, singleton design pattern resets fdp instead of static
    while(fdp.getAircraftData(type, airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt)){
        passengerJetFactory.push_back(AircraftData(airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt));
    }

}


AircraftData* PassengerJetFactory::getAircraft(char* craftName){
    for(int i = 0; i<passengerJetFactory.size(); i++){
        passengerJetFactory.at(i).getMake(airMake);
        if(strcmp(airMake, craftName) == 0){
            return &passengerJetFactory.at(i);
        }
    }
    return NULL;
}
