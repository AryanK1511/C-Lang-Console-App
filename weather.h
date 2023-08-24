////////////////////////////////////////////////////////////
// Macro's (usable by any file that includes this header) 
////////////////////////////////////////////////////////////

// Macros for the Maximum number of records 
// the program can process
#define MAX_RECS 250

// Macros for month info 
#define MONTHS 12
#define MONTH_NAME 10

// Macros for location info
#define LOCATIONS 8
#define LOCATION_NAME 15

// Macros for region info 
#define ALL_REGIONS 4
#define REGION_NAME 10

// Macros for table format
#define ALL_DATA_FORMAT 0
#define REGION_FORMAT 1
#define MONTH_FORMAT 2
#define LOCATION_FORMAT 3

// Macros for the sorting order
#define ASCENDING 1
#define DESCENDING 0


//////////////////////////////////////
// Structures
//////////////////////////////////////

struct Date
{
	int year;
	int month;
};

struct Location
{
	char name[LOCATION_NAME + 1];
	int regionCode;
};

struct WeatherRecord
{
	struct Date date;
	struct Location location;
	double precipAmt;
	char unit;
};

//------------------------------------

struct RegionSummary
{
	char regionName[REGION_NAME + 1];
	int regionCode;
	double regionPrecipitation;
};

struct MonthSummary
{
	char monthName[MONTH_NAME + 1];
	int monthNum;
	double monthPrecipitation;
};

struct LocationSummary
{
	char locationName[LOCATION_NAME + 1];
	double locationPrecipitation;
};


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTION
//////////////////////////////////////

// Displays the menu to the user
void menu(struct WeatherRecord* data, struct RegionSummary* regionInf,
	struct MonthSummary* monthInf, struct LocationSummary* locationInf, int recordsRead);


//////////////////////////////////////
// VIEW FUNCTIONS 
//////////////////////////////////////

// Displays all weather record data 
void ViewAllData(struct WeatherRecord* data, int recordsRead);

// Displays all data by grouping it by region and sorting it in descending order by precipitation
void ViewByRegion(struct WeatherRecord* data, struct RegionSummary* regionInf, int recordsRead);

// Displays all data by grouping it by month and sorting it in ascending order by precipitation
void ViewByMonth(struct WeatherRecord* data, struct MonthSummary* monthInf, int recordsRead);

// Displays all data by grouping it by location name and sorting it in descending order by precipitation
void ViewByLocationName(struct WeatherRecord* data, struct LocationSummary* locationInf, int recordsRead);


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Function to display table headers for different scenarios
void displayTableHeader(int table_format);

// Function to display total and average precipitation for different scenarios 
void displayTotalAverage(double totalPrecipitation, int table_format);


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Converts values from cm (centimeter) to mm (millimeter)
void conversion(struct WeatherRecord* data, int recordsRead);


//////////////////////////////////////
// FILE READING FUNCTION
//////////////////////////////////////

// Reads data from a file, stores it in  a struct && returns the number of records
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Returns a valid integer value
int inputInt(void);

// Returns an integer value (if it is in the permitted range)
int inputIntRange(int min, int max);


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for the user to input the "enter" key to continue
void pressContinue(void);
