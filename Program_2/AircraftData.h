#pragma once

#include <iostream>
#include <cstring>

class AircraftData{
    private:
        char airMake[32];
        char airType[32];
        double rateClimb;
        double wingspan;
        double length;
        double rateCruise;
        double cruisingAlt;

        double realAlt;
    public:
        AircraftData();
        AircraftData(char *make, char *type, double *climb, double *span, double *length, double *cruise, double *alt);
        void getMake(char *make) { strcpy(make, airMake);}
        void getType(char *type) { strcpy(type, airType);}
        double getRateClimb() { return rateClimb;}
        double getRateCruise() { return rateCruise;}
        double getCruisingAlt(){ return cruisingAlt;}

        int getRealAlt(int hr1, int min1, int hr2, int min2, int distance);
        void dump(std::ostream&);
};