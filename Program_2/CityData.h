
#pragma once
#include <iostream>
#include <cstring>


class CityData{
    private:
        char cityName[32];
        char cityState[32];
        char citySymbol[32];
        double lat;
        double lon;
    public:
        CityData(char *name, char *state, char *symbol, double *lats, double *lons);
        void getSymbol(char *symbol) { strcpy(symbol, citySymbol);}
        void getName(char *name) { strcpy(name, cityName);}
        void getState(char *name) {strcpy(name, cityState);}
        double getLat(){ return lat;}
        double getLon() { return lon;}

        void getLatLon(double &lats, double &lons);
        void dump(std::ostream&);
};