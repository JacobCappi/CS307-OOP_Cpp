#include "Simulation.h"


Simulation::Simulation(){

}

Simulation::~Simulation(){

}

void Simulation::init(){
// ----- Intro
    std::cout << "Welcome to the Program\nEnter file name: ";
    cin >> filename;
    printf("%s", filename);

    char cityFileName[32];
    char flightFileName[32];

    ifstream inFile;
    inFile.open(filename);

    if(inFile.fail()){
        cout << "Error: File failed to open";
        exit(0);
    }
    inFile >> cityFileName >> flightFileName;
    printf("%s %s %s", filename, cityFileName, flightFileName);

    int tmp = 1;
    std::cout << "\nEnter simulation run speed (1, 2, or 3): ";
    cin >> tmp;
    setRunSpeed(tmp);

// ----- END

// ----- City Init
    cdp.InitCityData(cityFileName);

    while(cdp.getCityData(cityName, cityState, citySymbol, &lat, &lon)){
        cityData.push_back(CityData(cityName, cityState, citySymbol, &lat, &lon));
    }
    cdp.getCitySymbolsArray(&citySymbolArr);
    cdp.getDistTable(&cityDistanceArr);
// ----- END

// ----- Flight Init
    fdp.InitFlightData(flightFileName);

    while(fdp.getAircraftData(airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt)){
        aircraftData.push_back(AircraftData(airMake, airType, &rateClimb, &wingspan, &length, &rateCruise, &cruisingAlt));
    }
    inFile.close();

    while(fdp.getFlightData(airline, planeType, &flightNum, cityDep, &hour, &minute, cityDes)){
        flightData.push_back(FlightData(airline, planeType, &flightNum, cityDep, &hour, &minute, cityDes));
    }
    fdp.getStartTime(&currentHr, &currentMin);
    return;
// ----- END

}

void Simulation::setRunSpeed(int speed){
    if(speed > 0 && speed <= 3){
        runSpeed = speed;
    }
    else{
        std::cout << "Runspeed Not permitted: exiting...";
        exit(0);
    }
}

void Simulation::runSim(){
    using namespace std::this_thread;
    using namespace std::chrono;

    while(true){
        std::cout << "\n+++++++++++++++++++++++++\n";
        printTime();
        std::cout << "+++++++++++++++++++++++++\n";
        printFlights();
        updateTime();

        sleep_for(seconds(1));
    }
}

// Report -> arrivals -> departures
void Simulation::printFlights(){
    for(int i =0;i<fdp.getFlightCount();i++){
        flightData[i].getStartTime(hour, minute);
        if(currentHr > hour || (currentHr == hour && currentMin >= minute)){
            if(!flightData[i].getHasDeparted()){
               flightData[i].setHasDeparted(true);
               printFlightDataDeparting(flightData[i]);
            }
            else{
            // awkward bug fix, will attend later
                int tmp1, tmp2;
                flightData[i].getEndTime(tmp1, tmp2);
                if( (currentHr > tmp1) || (currentHr == tmp1) && (currentMin >= tmp2)){
                    if(!flightData[i].getHasCompleted()){
                        printFlightDataArrival(flightData[i]);
                        flightData[i].setHasCompleted(true);
                    }
                }
                else if(!flightData[i].getHasCompleted()){
                    printFlightDataDepart(flightData[i]);
                }
            }
        }

    }

}
void Simulation::fetchCityInfo(){
    for(int i =0;i<cdp.getCityCount();i++){
        cityData[i].getSymbol(citySymbol);
        if(strcmp(citySymbol, cityDep) == 0){
            cityData[i].getName(cityName);
            cityData[i].getState(cityState);
            cityData[i].getLatLon(lat, lon);
        }
    }
}

void Simulation::fetchAircraftInfo(){
    for(int i=0;i<fdp.getAircraftCount();i++){
        aircraftData[i].getMake(airMake);
        if(strcmp(planeType, airMake) == 0){
            rateCruise = aircraftData[i].getRateCruise();
            cruisingAlt = aircraftData[i].getCruisingAlt();
            craftIndex = i;
        }
    }
}

void Simulation::printFlightDataDeparting(FlightData &currentFlight){
    std::cout << "------------------------------------------------\n";
    std::cout << "Now Departing: ";
    currentFlight.printInfoFormatted(std::cout);
    currentFlight.getCityDep(cityDep);
    index1 = fetchIndex();
    fetchCityInfo();
    std::cout << "\tDeparting from: " << cityName << ", " << cityState;

    currentFlight.getCityDes(cityDep);
    fetchCityInfo();
    index2 = fetchIndex();

    currentFlight.setDistance(fetchDistance());
    currentFlight.getPlaneType(planeType);

    fetchAircraftInfo();
    currentFlight.setEndTime(rateCruise);
    currentFlight.getEndTime(hour, minute);

    std::cout << "\n\t\tEnroute to: " <<  cityName << ", "<< cityState;
    std::cout << " at " <<currentFlight.getStartHour() << ":" << currentFlight.getStartMin() << std::endl;
    std::cout << "\n\tEstimated Time of Arrival: " << hour << ":"<< minute << endl;
    printTime();

    std::cout << "\n------------------------------------------------\n";
}



int Simulation::fetchIndex(){
    for(int i=0; i<cdp.getCityCount(); i++){
        if(strcmp(citySymbolArr[i], cityDep) == 0){
            return i;
        }
    }
    return 0;
}

int Simulation::fetchDistance(){
    return(cityDistanceArr[(index1*cdp.getCityCount())+index2]);
}

void Simulation::printFlightDataDepart(FlightData &currentFlight){
    std::cout << "------------------------------------------------\n";
    currentFlight.printInfoFormatted(std::cout);
    currentFlight.getCityDep(cityDep);
    fetchCityInfo();
    std::cout << "\tDeparts : " << cityDep << " (" << lat << ", " << lon << ") at ";
    std::cout << currentFlight.getStartHour() << ":" << currentFlight.getStartMin() << std::endl;

    double lat1 = lat;
    double lon1 = lon;
    currentFlight.getCityDes(cityDep);
    fetchCityInfo();

    currentFlight.getPlaneType(planeType);

    fetchAircraftInfo();
    currentFlight.getEndTime(hour, minute);

    std::cout << "\tArrives: " << cityDep << " (" << lat << ", " << lon << ") at ";
    std::cout << hour << ":" << minute;

    double lat2 = lat;
    double lon2 = lon;
    double coef;
    int dis = currentFlight.getDistance();
    coef = currentFlight.getFraction(currentHr, currentMin);

    int realAlt = aircraftData[craftIndex].getRealAlt(currentFlight.getStartHour(), currentFlight.getStartMin(), currentHr, currentMin, dis);

    currentFlight.getCityDep(cityDep);
    currentFlight.getCityDes(cityDes);

    std::cout << "\n\tCurrent Location: (" << (lat1 +((lat2-lat1)*coef)) << ", " << (lon1 +((lon2-lon1)*coef)) << ") ";
    std::cout << "\n\t\t" << (coef*(double)dis) << " from " << cityDep;
    std::cout <<", " << (dis - (coef*(double)dis)) << " miles to " << cityDes;

    std::cout << "\n\tCurrent Speed: " << rateCruise << " MPH";
    std::cout << "\n\tCurrent altitude: " << realAlt << " feet";

    std::cout << "\n------------------------------------------------\n";
}


void Simulation::printFlightDataArrival(FlightData &currentFlight){
    std::cout << "------------------------------------------------\n";
    std::cout << "Now Arriving: ";
    currentFlight.printInfoFormatted(std::cout);
    currentFlight.getCityDes(cityDep);

    fetchCityInfo();
    std::cout << "\t\tAt : " << cityName << ", " << cityState;

    currentFlight.getCityDep(cityDep);
    fetchCityInfo();

    std::cout << "\n\t\tFrom : " <<  cityName << ", "<< cityState << endl;
    printTime();

    std::cout << "\n------------------------------------------------\n";
}

void Simulation::printTime(){
    std::cout << "Current clock time: " << currentHr << ":" << currentMin << std::endl;
}

void Simulation::updateTime(){
    currentMin = (runSpeed*5)+currentMin;
    if(currentMin >= 60){
        currentMin -= 60;
        currentHr++;
    // Assuming pilots use 24 hr time
        if(currentHr >=24){
            currentHr = 0;
        }
    }
}

int main(){
    Simulation s;
    s.init();
    s.runSim();
    return 0;
}