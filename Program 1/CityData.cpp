#include "CityData.h"
CityData::CityData(char *name, char *state, char *symbol, double *lats, double *lons){
    strcpy(cityName, name);
    strcpy(citySymbol, symbol);
    strcpy(cityState, state);
    lat = *lats;
    lon = *lons;
}

void CityData::dump(std::ostream& o){
    o << cityName << cityState << citySymbol << lat << lon << "\n";
}

void CityData::getLatLon(double &lats, double &lons){
    lats = lat;
    lons = lon;
}

