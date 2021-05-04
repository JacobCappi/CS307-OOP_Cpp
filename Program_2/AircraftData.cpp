#include "AircraftData.h"

AircraftData::AircraftData(){
}
AircraftData::AircraftData(char *make, char *type, double *climb, double *span, double *size, double *cruise, double *alt){
    strcpy(airMake, make);
    strcpy(airType, type);
    rateClimb = *climb;
    wingspan = *span;
    length = *size;
    rateCruise = *cruise;
    cruisingAlt = *alt;
}

void AircraftData::dump(std::ostream &o){
    o << airMake << airType << rateClimb << wingspan << length << rateCruise << cruisingAlt << "\n";
}


int AircraftData::getRealAlt(int hr1, int min1, int hr2, int min2, int distance){
// bugs, need to take a look
    int time1, time2, time3;
    time1 = (hr1 * 60) + min1; // start time
    time2 = (hr2 * 60) + min2; // elapsed

    time3 = time2 - time1;

    int chunk1, chunk2;

    int dToMax = cruisingAlt/rateCruise;
    return cruisingAlt; // placeholder for now, as not working
    if( (2*dToMax) < distance){
        chunk1 = dToMax;
        chunk2 = distance - dToMax;
        if(rateClimb*time3 <= chunk1) {
            return (time3+rateClimb);
        }
        else if(rateClimb*time3 > chunk2){
            return(cruisingAlt*(time3 - (time3+1)));
        }
        else{
            return(cruisingAlt);
        }
    }
    else{
        chunk1 = distance/2;
        chunk2 = distance;
        if(rateClimb*time3 < chunk1){
            return(time3*rateClimb);
        }
        else{
            return( chunk2-((1/time3)*rateClimb));
        }
    }


}
