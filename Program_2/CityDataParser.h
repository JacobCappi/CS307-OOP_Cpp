//========================================================
// CityDataParser.h
// Interface file for the city data parser class.
//
// Author: Dr. Rick Coleman
// Date: July 2011
//========================================================
#pragma once

#include "fstream"
#include <cstring>

using namespace std;

class CityDataParser
{
	private:
		int m_iCityCount;
		char m_sDataFile[32];
		bool m_bDataFileOK;
		fstream	*inFile;
		CityDataParser();					// Constructor

	public:
		~CityDataParser();					// Destructor
		static CityDataParser *getInstance();
		void InitCityData(const char *dataFile);	// Read all data from the data file
		int getCityCount();
		bool getCityData(char *name, char *state, char *symbol, double *lat, double *lon);
		void getCitySymbolsArray(char ***array);
		void getDistTable(double **array);
		bool getNextLine(char *buffer, int n);

};

