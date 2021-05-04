
#pragma once
#include <iostream>
#include <cstring>

class FlightData{
    private:
        char airline[32];
        char planeType[32];
        int flightNum;
        char cityDep[4];
        int hour;
        int minute;

        bool hasDeparted;
        bool hasCompleted;

        int endHour;
        int endMinute;
        int distance;

        char cityDes[4];
    public:
        FlightData(char *line, char *plane, int *num, char *dep, int *hr, int *min, char *des);
        void getPlaneType(char *plane){ strcpy(plane, planeType);}

        int getFlightNumber(){return flightNum;}
        void getCityDep(char *dep){ strcpy(dep, cityDep);}
        void getCityDes(char *des){ strcpy(des, cityDes);}

        void setHasDeparted(bool flag) { hasDeparted = flag;}
        bool getHasDeparted(){ return hasDeparted;}

        void setHasCompleted(bool flag) { hasCompleted = flag;}
        bool getHasCompleted(){ return hasCompleted;}

        void getStartTime(int &hr, int &min);
        int getStartHour(){return hour;}
        int getStartMin(){return minute;}

        void getEndTime(int &hr, int &min);
        void setEndTime(int speed);

        void printInfoFormatted(std::ostream &o);
        void dump(std::ostream &o);

        void setDistance(int d){ distance = d;}
        int getDistance(){return distance;}

        double getFraction(int, int);
};