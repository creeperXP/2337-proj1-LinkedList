/*
Name: Nathan Han
netID: nxh230021
Date: 9/14/2024
Driver class function definitions
*/
#include "Driver.h"
#include <iomanip>
#include <cmath>
#include <iostream>

//set static int to default value
int Driver::comparison_var = 0;

/*
overloaded << operator to print driver object in the format of 2 decimal places,
<name><tab><area><newline>
*/
std::ostream &operator<<(std::ostream &out, const Driver &driver)
{
    out << std::fixed << std::setprecision(2);
    out << driver.name << '\t' << driver.area << std::endl;
    return out;
}

/*
overloaded > operator return comparison of area or name
if static variable == 1, return comparison of area
else return comparison of name
ex: return true if area of left operand > right operand
*/
bool Driver::operator>(const Driver &driver) const
{
    if (comparison_var == 1)
    {
        return area > driver.area;
    }
    return name > driver.name;
}

/*
overloaded < operator return comparison of area or name
if static variable == 1, return comparison of area
else return comparison of name
ex: return true if area of left driver < right driver
*/
bool Driver::operator<(const Driver &driver) const
{
    if (comparison_var == 1)
    {
        return area < driver.area;
    }
    return name < driver.name;
}

/*
overloaded == operator return comparison of area or name
if static variable == 1, return comparison of area
else return comparison of name
ex: return false if name of left operand != right operand
*/
bool Driver::operator==(const std::string &command) const
{
     if (Driver::comparison_var == 1)
    {
        /*
        when comparing area, only compare 2 decimal places
        */
        double commandround = round(std::stod(command)*100)/100;
        double arearound = round(area*100)/100;
        return arearound == commandround;
    }
    return name == command;
}

