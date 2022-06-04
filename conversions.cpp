#include <iostream>

using namespace std;

int main(){
    
    // Declare and initialize variables and constants
    double radius = 0;
    double area_circle = 0;
    double distance_meter = 0;
    double inch = 0;
    double feet = 0;
    double decimal_feet = 0;
    double furlong = 0;
    double light_time = 0;
    const double pi = 3.141592653589793;
    const double meter_to_feet = 3.280839895;
    const double feet_to_inch = 12;
    const double meter_to_furlong= 201.168;
    const double spd_light = 299792458;
    
    // Title
    cout << "CIRCLE AREA" << endl;
    cout << "-----------" << endl;
    
    // Ask user for radius
    cout << "Enter radius: ";
    cin >> radius;
    
    // Calculate area of circle and print it
    area_circle =  pi * radius * radius;
    cout << "A circle with radius = " << radius << " has an area = " << area_circle << endl;
    cout << endl;
    
    // Title
    cout << "DISTANCE" << endl;
    cout << "---------" << endl;
    
    // Ask user for distance in meters
    cout << "Enter distance in meters: ";
    cin >> distance_meter;
    
    // Conversions from meters to other units
    feet = distance_meter * meter_to_feet;
    decimal_feet = feet - int(feet);
    inch =  decimal_feet * feet_to_inch;
    
    furlong = distance_meter / meter_to_furlong;
    
    light_time = distance_meter / spd_light;
    
    // Printing conversions
    cout << distance_meter << " meters = " << int(feet) << "\' " << inch << "\""  << endl;
    cout << distance_meter << " meters = " << furlong << " furlongs " << endl;
    cout << "It takes " << light_time << "s for light to travel "  << distance_meter << "m in a vacuum. " << endl;
    
    return 0;
}

