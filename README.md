# C Language Console Application

This program is designed to analyze weather data for the province of Ontario. It reads weather data from a file, processes it, and provides various ways to view and analyze the data. The program offers the following functionalities:

1. **View All Data:**
   This option displays all weather records in a tabular format. It shows the year, month, precipitation amount, unit (mm or cm), region code, and location name. Data is displayed in groups of 15 records.

2. **View by Region (Descending Precipitation):**
   This option groups the data by region and displays the total precipitation for each region. Regions are sorted in descending order based on precipitation amounts. The total and average precipitation for all regions are displayed at the end.

3. **View by Month (Ascending Precipitation):**
   Data is grouped by month, and the program displays the total precipitation for each month. Months are sorted in ascending order based on precipitation amounts. The total and average precipitation for all months are displayed at the end.

4. **View by Location Name (Descending Precipitation):**
   Data is grouped by location name, and the program displays the total precipitation for each location. Locations are sorted in descending order based on precipitation amounts. The total and average precipitation for all locations are displayed at the end.

5. **Conversion from cm to mm:**
   The program offers a utility to convert precipitation values from centimeters (cm) to millimeters (mm).

6. **File Reading:**
   The program reads weather data from a file named "weatherData.txt". It reads the year, month, precipitation amount, unit, region code, and location name from each line in the file. It can process up to 250 records.

7. **User Input Handling:**
   The program provides user input functions to ensure valid integer inputs and input within specified ranges. It also includes functions to clear the standard input buffer and wait for the user to press the "enter" key to continue.

8. **User Interface:**
   The user interface is presented in the form of a menu. Users can select different options by inputting the corresponding number. The program continues to display the menu until the user chooses to exit.

9. **Data Structures:**
   The program uses various data structures to store weather records, region summaries, month summaries, and location summaries. These structures help organize and present data effectively.

10. **Sorting and Display:**
    The program implements sorting algorithms to arrange data based on different criteria. Data is displayed in formatted tables with appropriate headers and totals.

11. **Macros and Constants:**
    The program uses macros to define constants such as maximum records, number of months, number of locations, and more. These macros enhance code readability and maintainability.

12. **Modularization:**
    The program is divided into several source files to enhance code organization and maintainability. Different functionalities are encapsulated into separate functions for clarity.
