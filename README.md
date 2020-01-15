# Know your Fuel Price by location
**This program gives fuel prices at any location. Just input latitude and longitude of the desired location and you will be able to know the nearest fuel outlet and the fuel price there.**

# Example

*Below data is indicative, for demonstration purpose only.*

    Enter Latitude of location: 13.362281
    Enter Longitude of location: 74.875378
    
    Nearest Outlet Customer Code: 11223344 at 13.421113, 74.834903
    Petrol Price: 67.07
    Diesel price: 60.10
   
   [How to Find Latitude & Longitude of a Place on Phone/Computer?](https://support.google.com/maps/answer/18539)

# Use Cases
 - **Many organisations make payments to vendors with Diesel price as an important component in PO. Price at a particular location can be monitored on daily basis/weekly basis or any other logic, to dynamically include price changes in invoice.**
 - Find nearest outlet with lowest price, without having to pay for Maps API.
 - Run this as a Web Service to provide customer convenience on locating outlet and pricing info.

# Usage

**Execute the cpp file as below:**
Clone this repository or download all files and place them in a particular folder. Open Terminal and navigate to that folder and run `FuelPriceLatLong.cpp`

    g++ FuelPriceLatLong.cpp
    ./a.out


    Enter Latitude of location: 13.362281
    Enter Longitude of location: 74.875378
    
    Nearest Outlet Customer Code: 11223344 at 13.421113, 74.834903
    Petrol Price: 67.07
    Diesel price: 60.10

# Additional Data Files

 1. **OutletCsvData.csv**:  This file has to contain latitude, longitude, Outlet Code of all outlets to be included for search. Indicative sample file is provided in the repository.
 2. **RSPData.csv**: This file has to contain data on Customer Code, Price of Petrol and Diesel. Indicative sample file is provided in the repository.

# Pending Tasks & Future Scope

 - [ ] **Run this as a Website and provide Fuel Price Finding Service**
 - [ ] Return results of up to 10 outlets in the increasing order of distance from entered location
 - [ ] Include clickable link to plot nearest outlet in the results
