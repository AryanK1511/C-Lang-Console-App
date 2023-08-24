#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "weather.h"

int main()
{
    // Opening the weather data file
    FILE* fp = fopen("weatherData.txt", "r");

    // Setting the structs to the safe empty space
    struct Date date = { 0, 0 };
    struct Location location = { {0}, 0 };
    struct WeatherRecord data[MAX_RECS] = { {date, location, 0, 0} };

    // Initializing the structs with the necessary information
    struct RegionSummary regionInf[ALL_REGIONS] = { {"Western", 10, 0}, {"Northern", 20, 0},
        {"Eastern", 30, 0}, {"Central", 40, 0} };
    struct MonthSummary monthInf[MONTHS] = { {"January", 1, 0}, {"February", 2, 0}, {"March", 3, 0},
        {"April", 4, 0}, {"May", 5, 0}, {"June", 6, 0}, {"July", 7, 0}, {"August", 8, 0},
        {"September", 9, 0}, {"October", 10, 0}, {"November", 11, 0}, {"December", 12, 0} };
    struct LocationSummary locationInf[LOCATIONS] = { {"Chatham-Kent", 0}, {"Halton", 0}, {"Renfrew", 0},
        {"Kenora", 0}, {"Simcoe", 0}, {"Essex", 0}, {"Ottawa", 0}, {"Thunder Bay", 0} };

    // Storing the number of records read from the file
    int recs = importWeatherDataFile(fp, data, MAX_RECS);

    // Convers cm (centimeter) values to mm (millimeter values)
    conversion(data, recs);

    // Display the menu
    menu(data, regionInf, monthInf, locationInf, recs);

    return 0;
}
