/*
*************************************************************************************************
-------------------------------------------------------------------------------------------------
                               IPC144 Final Assessment - weather.c
-------------------------------------------------------------------------------------------------
  #  |  Group Member         |  Student Number  |  Email                       |  Section
_________________________________________________________________________________________________
  1  |  Arina Kolodeznikova  |  145924213       |  akolodeznikova@myseneca.ca  |  NJJ
-------------------------------------------------------------------------------------------------
  2  |  Aryan Khurana        |  145282216       |  akhurana22@myseneca.ca      |  NJJ
-------------------------------------------------------------------------------------------------
*************************************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "weather.h"


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTION
//////////////////////////////////////

// Displays the menu to the user
void menu(struct WeatherRecord* data, struct RegionSummary* regionInf,
    struct MonthSummary* monthInf, struct LocationSummary* locationInf, int recordsRead)
{
    // Variable to store the user's choice
    int selection;
   
    // Menu && Options
    do
    {
        printf("=======================================================\n"
            "         Ontario Weather Analysis Service\n"
            "                   Year : 2021\n"
            "=======================================================\n"
            "1. View all data\n"
            "2. View by region(sorted DESCENDING by precip.)\n"
            "3. View by month(sorted ASCENDING by precip.)\n"
            "4. View by location name(sorted DESCENDING by precip.)\n"
            "-------------------------------------------------------\n"
            "0. Exit\n"
            "-------------------------------------------------------\n"
            "Selection: ");

        selection = inputIntRange(0, 4);
        putchar('\n');

        switch (selection)
        {
        case 0:
            printf("Application Terminated!\n\n");
            break;

        case 1:
            ViewAllData(data, recordsRead);
            putchar('\n');
            break;

        case 2:
            ViewByRegion(data, regionInf, recordsRead);
            putchar('\n');
            break;

        case 3:
            ViewByMonth(data, monthInf, recordsRead);
            putchar('\n');
            break;

        case 4:
            ViewByLocationName(data, locationInf, recordsRead);
            putchar('\n');
            break;
        }

    } while (selection);
}


//////////////////////////////////////
// VIEW FUNCTIONS 
//////////////////////////////////////

// Displays all weather record data 
void ViewAllData(struct WeatherRecord* data, int recordsRead)
{
    // Variables
    int index;

    // Displaying table header
    displayTableHeader(ALL_DATA_FORMAT);

    for (index = 0; index < recordsRead; index++)
    {

        // Displaying only 15 elements at a single time
        if (index % 15 == 0 && index != 0)
        {
            putchar('\n');
            pressContinue();
        }

        // Printing the data
        printf("%d    %02d     %6.1lf    %c     %d %s\n",
            data[index].date.year, data[index].date.month, data[index].precipAmt,
            data[index].unit, data[index].location.regionCode, data[index].location.name);
    }
}

// Displays all data by grouping it by region and sorting it in descending order by precipitation
void ViewByRegion(struct WeatherRecord* data, struct RegionSummary* regionInf, int recordsRead)
{
    // Defining essential variables and data structures
    int i, j;
    struct RegionSummary tmp_var;

    // Variable to calculate total precipitation
    double totalPrecipitation = 0;

    // Displaying table header
    displayTableHeader(REGION_FORMAT);

    // Initializing the precipitation to zero every time the function is called
    for (i = 0; i < ALL_REGIONS; i++) 
    {
         regionInf[i].regionPrecipitation = 0;
    }

    // Calculating the total precipitation amount (overall & per region)
    for (i = 0; i < recordsRead; i++)
    {
        for (j = 0; j < ALL_REGIONS; j++)
        {
            if (data[i].location.regionCode == regionInf[j].regionCode)
            {
                regionInf[j].regionPrecipitation += data[i].precipAmt;
            }
        }
        totalPrecipitation += data[i].precipAmt;
    }

    // Sorting in descending order
    for (i = ALL_REGIONS - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (regionInf[j].regionPrecipitation < 
                regionInf[j + 1].regionPrecipitation)
            {
                tmp_var = regionInf[j];
                regionInf[j] = regionInf[j + 1];
                regionInf[j + 1] = tmp_var;
            }
        }
    }

    // Printing the data for each region
    for (i = 0; i < ALL_REGIONS; i++)
    {
        printf("%6d %s       %d\n", regionInf[i].regionCode, regionInf[i].regionName,
            (int)round(regionInf[i].regionPrecipitation));
    }

    // Displaying total and average precipitation 
    displayTotalAverage(totalPrecipitation, REGION_FORMAT);
}

// Displays all data by grouping it by month and sorting it in ascending order by precipitation
void ViewByMonth(struct WeatherRecord* data, struct MonthSummary* monthInf, 
    int recordsRead)
{
    // Defining essential variables and data structures
    int i, j;
    struct MonthSummary tmp_var;

    // Variable to calculate total precipitation
    double totalPrecipitation = 0;

    // Displaying table header
    displayTableHeader(MONTH_FORMAT);

    // Initializing the precipitation to zero every time the function is called
    for (i = 0; i < MONTHS; i++) 
    {
         monthInf[i].monthPrecipitation = 0;
    }

    // Calculating the total precipitation amount (overall & per month)
    for (i = 0; i < recordsRead; i++)
    {
        for (j = 0; j < MONTHS; j++)
        {
            if (data[i].date.month == monthInf[j].monthNum)
            {
                monthInf[j].monthPrecipitation += data[i].precipAmt;
            }
        }
        totalPrecipitation += data[i].precipAmt;
    }

    // Sorting in ascending order
    for (i = MONTHS - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (monthInf[j].monthPrecipitation > 
                monthInf[j + 1].monthPrecipitation)
            {
                tmp_var = monthInf[j];
                monthInf[j] = monthInf[j + 1];
                monthInf[j + 1] = tmp_var;
            }
        }
    }

    // Printing the data for each month
    for (i = 0; i < MONTHS; i++)
    {
        printf("%-10s      %d\n", monthInf[i].monthName,
            (int)round(monthInf[i].monthPrecipitation));
    }

    // Displaying total and average precipitation 
    displayTotalAverage(totalPrecipitation, MONTH_FORMAT);
}

// Displays all data by grouping it by location name and sorting it in descending order by precipitation
void ViewByLocationName(struct WeatherRecord* data, struct LocationSummary* locationInf, 
    int recordsRead)
{
    // Defining essential variables and data structures
    int i, j;
    struct LocationSummary tmp_var;

    // Variable to calculate total precipitation
    double totalPrecipitation = 0;

    // Displaying table header
    displayTableHeader(LOCATION_FORMAT);

    // Initializing the precipitation to zero evertime the function is called
    for (i = 0; i < LOCATIONS; i++) 
    {
         locationInf[i].locationPrecipitation = 0;
    }

    // Calculating the total precipitation amount (overall & per location)
    for (i = 0; i < recordsRead; i++)
    {
        for (j = 0; j < LOCATIONS; j++)
        {
            if (strcmp(data[i].location.name, locationInf[j].locationName) == 0)
            {
                locationInf[j].locationPrecipitation += data[i].precipAmt;
            }
        }
        totalPrecipitation += data[i].precipAmt;
    }

    // Sorting in ascending order
    for (i = LOCATIONS - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (locationInf[j].locationPrecipitation < 
                locationInf[j + 1].locationPrecipitation)
            {
                tmp_var = locationInf[j];
                locationInf[j] = locationInf[j + 1];
                locationInf[j + 1] = tmp_var;
            }
        }
    }

    // Printing the data for each location
    for (i = 0; i < LOCATIONS; i++)
    {
        printf("%15s %10d\n", locationInf[i].locationName,
            (int)round(locationInf[i].locationPrecipitation));
    }

    // Displaying total and average precipitation 
    displayTotalAverage(totalPrecipitation, LOCATION_FORMAT);
}


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Function to display table headers for different scenarios
void displayTableHeader(int table_format)
{
    if (table_format == 0)
    {
        printf("Year Month Precip.Amt Unit Region Name\n");
        printf("---- ----- ---------- ---- ------ ---------------\n");
    }
    else if (table_format == 1)
    {
        printf("Region Name     Precip(mm)\n");
        printf("------ -------- ----------\n");
    }
    else if (table_format == 2)
    {
        printf("Month     Precip(mm)\n");
        printf("--------- ----------\n");
    }
    else if (table_format == 3)
    {
        printf("Location        Precip(mm)\n");
        printf("--------------- ----------\n");
    }
}

// Function to display total and average precipitation for different scenarios 
void displayTotalAverage(double totalPrecipitation, int table_format)
{
    if (table_format == 1)
    {
        printf("------ -------- ----------\n");
        printf("         Total:      %d\n", (int)round(totalPrecipitation));
        printf("       Average:   %.2lf\n", totalPrecipitation / ALL_REGIONS);
    }
    else if (table_format == 2)
    {
        printf("--------- ----------\n");
        printf("   Total:      %d\n", (int)round(totalPrecipitation));
        printf(" Average:    %.2lf\n", totalPrecipitation / MONTHS);
    }
    else if (table_format == 3)
    {
        printf("--------------- ----------\n");
        printf("         Total:      %d\n", (int)round(totalPrecipitation));
        printf("       Average:    %.2lf\n", totalPrecipitation / LOCATIONS);
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Converts values from cm (centimeter) to mm (millimeter)
void conversion(struct WeatherRecord* data, int max)
{
    int j;

    for (j = 0; j < max; j++)
    {
        if (data[j].unit == 'c')
        {
            data[j].precipAmt *= 10;
        }
    }
}


//////////////////////////////////////
// FILE READING FUNCTION
//////////////////////////////////////

// Reads data from a file, stores it in  a struct && returns the number of records
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max)
{
    int recs = 0;

    if (fp != NULL)
    {
        while (recs < max &&
            fscanf(fp, "%d,%d,%lf,%c,%d,%15[^\n]\n",
                &data[recs].date.year, &data[recs].date.month,
                &data[recs].precipAmt, &data[recs].unit,
                &data[recs].location.regionCode,
                data[recs].location.name) == 6)
        {
            recs++;
        }
    }

    return recs;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Returns a valid integer value
int inputInt(void)
{
    int value = 0;
    char intChar;
    do
    {
        scanf("%d%c", &value, &intChar);
        if (intChar != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }

    } while (intChar != '\n');
    return value;
}

// Returns an integer value (if it is in the permitted range)
int inputIntRange(int min, int max)
{
    int value = 0;
    do
    {
        value = inputInt();
        if (value < min || value > max)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", 
                min, max);
        }
    } while (value < min || value > max);
    return value;
}


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void pressContinue(void)
{
    printf("< Press [ENTER] key to continue >");
    clearInputBuffer();
    putchar('\n');
}

