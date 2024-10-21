/*
The Driver class allows Driver objects to be made, with no parameters or
with a name parameter to initialize the name of the Driver.
Methods include changing/accessing name and area, overloaded < > and ==
operators to compare driver data, and overloaded << operator to print the data
within the driver object
*/
#ifndef DRIVER_H
#define DRIVER_H
#include <string>
#include <iostream>

class Driver
{
    public:
        /*
        default and overloaded Driver constructors that may initialize 
        Driver with a name or default values of "" and area 0.0
        */
        Driver(){name=""; area=0.0;}
        Driver(std::string name) {this->name=name;}

        //accessor functions for driver name and area
        std::string getName() const {return name;};
        double getArea() const {return area;};

        //mutator functions to change name and area of driver
        void setName(std::string name) {this->name = name;}
        void setArea(double area) {this->area = area;};

        //accessor and mutator method for static variable
        static int getComparisonVar() {return comparison_var;}
        static void setComparisonVar(int num) {comparison_var = num;}

        /*
        overloaded < > and == operators return comparison of area or name
        if static variable == 1, return comparison of area
        else return comparison of name
        */
        bool operator<(const Driver&) const;
        bool operator>(const Driver&) const;
        bool operator==(const std::string&) const;

        /*
        overloaded << operator to print driver object in the format of 2 decimal places,
        <name><tab><area><newline>
        */
        friend std::ostream& operator<<(std::ostream& out, const Driver& driver);

    private:
        std::string name;
        double area;
        /*
        the static int is set to 1 in main if comparison is to be made
        by area or if the command is to sort by area/find an area
        */
        static int comparison_var;
};
#endif
