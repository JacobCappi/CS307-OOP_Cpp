#include "FlightData.h"

FlightData::FlightData(char *line, char *plane, int *num, char *dep, int *hr, int *min, char *des){
    strcpy(airline, line);
    strcpy(planeType, plane);
    flightNum = *num;
    strcpy(cityDep, dep);
    hour = *hr;
    minute = *min;
    strcpy(cityDes, des);

    hasDeparted = false;
    hasCompleted = false;
}

void FlightData::getStartTime(int &hr, int &min){
    hr = hour;
    min = minute;
}

void FlightData::dump(std::ostream &o){
    o << airline << planeType << flightNum << cityDep << cityDes << "\n";
}

void FlightData::printInfoFormatted(std::ostream &o){
    if(strcmp(airline, "Delta") == 0 || strcmp(airline, "American") == 0 || strcmp(airline, "United") == 0){
        o << airline << " Airlines Flight " << flightNum << " - " << planeType << "\n";
    }
    else{
        o << airline << " Flight " << flightNum << " - " << planeType << "\n";
    }
}

void FlightData::setEndTime(int speed){
    int minuteAdd;
    int hourAdd;
    // weird behavior, bugfix, temperary
    double distanceToHour;
    int distanceToMinute;
    distanceToHour = (double)distance/(double)speed;
    distanceToMinute = (int)distanceToHour;

    minuteAdd = (int)((distanceToHour-(double)distanceToMinute)*60.0);
    hourAdd = distanceToMinute;

    endHour = hour + hourAdd;
    if(endHour >= 24){
        endHour -= 24;
    }
    endMinute = minute + minuteAdd;
    if(endMinute >= 60){
        endHour++;
        endMinute -=60;
    }
}

void FlightData::getEndTime(int &hr, int &min){
    hr = endHour;
    min = endMinute;
}

double FlightData::getFraction(int cHr, int cMin){
    int time1, time2, time3;
    time1 = (hour * 60) + minute;
    time2 = (cHr * 60) + cMin;
    time3 = (endHour * 60) + endMinute;

    time2 -= time1;
    time3 -= time1;

    return (double)((double)time2 / (double)time3);
}