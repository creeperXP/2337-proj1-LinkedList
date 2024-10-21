
/*
This program reads a file containing driver names and coordinates, calculates the area the driver
traveled, and stores each driver in a linked list.
A second file is read that gives commands to find a specific area/driver or sort
the drivers based on area or driver name (ASCII)
*/

// include files that contain classes to make objects (linked list, driver, node)
// and needed functions and members such as ifstream, fabs, and isdigit
#include "Node.h"
#include "Driver.h"
#include "LinkedList.h"
#include <fstream>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// function prototypes
void readRoutes(LinkedList<Driver> &, ifstream &);
void readCommands(LinkedList<Driver> &, ifstream &);
double getArea(string);
bool validateCommand(string);
bool validateCoord(string);
bool validateName(string);
bool validateNumber(string);

int main()
{
    LinkedList<Driver>* drivers = new LinkedList<Driver>;
    ifstream in;
    string routes;
    string commands;

    // prompt user to enter filename containing driver names and coordinates, stores in string
    cout << "Enter a filename for driver routes" << endl;
    cin >> routes;

    // prompt user for 2nd file to read commands, store in string
    cout << "Enter a filename for driver commands" << endl;
    cin >> commands;

    //read first file (routes)
    // if file opens successfully, then read the file by calling the readRoutes function, then close file
    in.open(routes);
    if (!in.fail())
    {
        readRoutes(*drivers, in);
    }
    in.close();

    // print linked list of drivers (name area) using overloaded <<
    cout << *drivers << endl;   

    //read second file (commands)
    // if file opens successfully, then read the file by calling the readCommands function, then close file
    in.open(commands);
    if (!in.fail())
    {
        readCommands(*drivers, in);
    }
    in.close();
    
    delete drivers;

    return 0;
}

/*
the readRoutes function takes the reference of a linked list object
(which is the driver list) and the reference of the ifstream object to
get each line of the file containing driver names and coordinates.
It checks to make sure formatting of name and coordinates
are valid by calling other validation functions
*/
void readRoutes(LinkedList<Driver>& list, ifstream &in)
{
    string line;

    /*while there is a line of driver/coordinates to read
    separate the driver name and coordinates string by finding the
    index of the first coordinate pair comma, then backtracking
    to find the space between the name and first coord pair*/
    while (getline(in, line))
    {
        // if nothing in line, continue while loop for next line
        if (line.empty())
        {
            continue;
        }

        string coordsub;
        string namesub;

        /*
        find comma index of first coordinate pair comma, then
        find the space between the name and first coord pair
        by rfind (last occurence of space before comma), then separate
        into different strings
        */
        int commaindex = line.find(",");
        int spaceindex = line.rfind(" ", commaindex);

        namesub = line.substr(0, spaceindex);
        coordsub = line.substr(spaceindex + 1);

        /*check to see if the name is a valid name and the coordinates string
        has all valid coordinates. If so, then create a new driver object
        with the name and calculate/set driver area using coordinates.
        Assign a node to the driver and insert the node into the linked list*/
        if (validateCoord(coordsub) && validateName(namesub))
        {
            Driver driver(namesub);
            driver.setArea(getArea(coordsub));
            Node<Driver> *drivernode = new Node(driver);
            list.insertNode(drivernode);
        }
    }
}

/*
the readCommands function takes the reference of a linked list object
(which is the driver list) and the reference of the ifstream object to
get each line of the file containing commands.
It checks to make sure formatting of commands
are valid and to follow the commands by calling other validation functions
*/
void readCommands(LinkedList<Driver> &list, ifstream &in)
{
    string command;
    while (getline(in, command))
    {
        // while there is a line in the file, check to see if command is valid
        if (validateCommand(command))
        {
            /*if command contains the word sort, check if its sort area or
            sort driver. If it is sort area, set the Driver class static variable
            to 1 to make sure overloaded comparison operators compare driver area*/
            if (command.find("sort") != string::npos)
            {
                if (command.find("area") != string::npos)
                {
                    Driver::setComparisonVar(1);
                }
                // after sorting list based on name or area, print the list using overloaded << operator
                list.sortList();
                cout << list << endl;
            }
            /*if a valid command is not sorting list, it must be to find a name or area,
            so go through the linked list to see if the data within the list
            is equal to command*/
            else
            {
                /*
                if command is a number, set the static variable of driver class
                to 1 so that the overloaded comparison operators compare the driver area,
                not the driver names 
                */
                if (validateNumber(command))
                {
                    Driver::setComparisonVar(1);
                }
                
                /*
                nodes to see if the current node has the data equal to command
                and node to carry that driver data to print
                */
                Node<Driver> *current = list.getHead();
                Node<Driver> *found;

                bool foundData = false;
                while (current)
                {
                    /*while there are still elements in list, check if the
                    current driver in the node of the list is equal to command
                    (determined by overloaded == operator and static variable: 1 if compare area)
                    */
                    if (current->getDriver() == command)
                    {
                        // if the data is equal, set foundData to true to indicate data is found
                        // break out of the while loop to print the data
                        foundData = true;
                        found = current;
                        break;
                    }
                    // if data not equal, continue to go through the linked list
                    current = current->getNextNode();
                }

                /*
                if data is equal to something inside a driver object,
                print that data, else print the data is not found 
                (2 decimal places if it is an area)
                */
                if (foundData)
                {
                    if (Driver::getComparisonVar() == 1)
                    {
                        cout << *found;
                    }
                    else
                    {
                        cout << *found;
                    }
                }
                else
                {
                    if (Driver::getComparisonVar() == 1)
                    {
                        cout << setprecision(2) << stod(command) << " not found " << endl;
                    }
                    else
                    {
                        cout << command << " not found " << endl;
                    }
                }
            }
        }
        // reset the Driver static comparison variable to 0 for the next command line
        // makes sure not comparing area/name twice in a row
        Driver::setComparisonVar(0);
    }
}

/*
the getArea function takes a string (the coordinates string)
and uses substrings to split the first 2 coordinate pairs.
Using the formula (x1+x2)*(y2-y1), calculate a sum,
reuse the 2nd coordinate pair
as the first pair for the next calculation.
Return the absolute value of this sum/2 to get the area travelled
*/
double getArea(string coordstring)
{
    // keep track of remaining coordinates
    string coordcheck = coordstring;

    // store x and y coords
    double xcoord1;
    double ycoord1;
    double xcoord2;
    double ycoord2;
    string firstcoordpair;
    string nextcoordpair;
    int commaindex;
    double sum;

    // find initial space indexes for 1st coord pair and 2nd coord pair to store
    int spaceindex1st = coordcheck.find(" ");
    int spaceindexnext = coordcheck.find(" ", spaceindex1st + 1);

    while (spaceindexnext != -1)
    {
        /*
        while not the end of coord line, store the first coord pair and next coord pair using
        the space index of the first coord pair and next coord pair
        */
        firstcoordpair = coordcheck.substr(0, spaceindex1st);
        nextcoordpair = coordcheck.substr(spaceindex1st + 1, spaceindexnext);

        /*
        separate the x and y coords for each coord pair by finding index
        of commas for each coord pair
        */
        commaindex = firstcoordpair.find(',');
        xcoord1 = stod(firstcoordpair.substr(0, commaindex));
        ycoord1 = stod(firstcoordpair.substr(commaindex + 1));

        commaindex = nextcoordpair.find(',');
        xcoord2 = stod(nextcoordpair.substr(0, commaindex));
        ycoord2 = stod(nextcoordpair.substr(commaindex + 1));

        /*
        add the product to total sum using the formula (x2+x1)*(y2-y1)
        */
        sum += (xcoord2 + xcoord1) * (ycoord2 - ycoord1);

        /*
        store the remaining coord pairs in coordcheck, keeping the 2nd coord pair
        of the last product done (x2-->x1 for next sum product)
        */
        coordcheck = coordcheck.substr(spaceindex1st + 1);

        // find next space index for next coord pairs: will cause while loop break if at 2nd to last coord pair
        spaceindex1st = coordcheck.find(" ");
        spaceindexnext = coordcheck.find(" ", spaceindex1st + 1);
    }
    /*
    when last 2 coord pairs:
    sets the most recent coordpair used in the product beforehand to firstcoordpair
    sets last coordpair to nextcoordpair
    */
    firstcoordpair = nextcoordpair;
    nextcoordpair = coordcheck.substr(spaceindex1st + 1);

    /*
    separate x and y coords based on comma index, then add
    the product (x2+x1)*(y2-y1) to sum
    */
    commaindex = firstcoordpair.find(',');
    xcoord1 = stod(firstcoordpair.substr(0, commaindex));
    ycoord1 = stod(firstcoordpair.substr(commaindex + 1));

    commaindex = nextcoordpair.find(',');
    xcoord2 = stod(nextcoordpair.substr(0, commaindex));
    ycoord2 = stod(nextcoordpair.substr(commaindex + 1));

    sum += (xcoord2 + xcoord1) * (ycoord2 - ycoord1);

    /*
    return absolute value sum/2 as the formula for polygon area
    given coordinates is:
    (1/2)(absolute value of (x2+x1)*(y2-y1) for all coord pairs)
    */
    return fabs(sum / 2.0);
}

/*
the validateCommand function takes a string (command from 2nd file)
and checks to see if it is "sort area", "sort driver", a valid driver name,
or valid driver area by calling the validateName and validateNumber
functions
Return: true if command can be used: string or area to pair with a specific
driver obj, or sorting the list by area/driver
Return: false if invalid
*/
bool validateCommand(string command)
{
    /*
    "sort area" and "sort driver" are the only valid commands to sort the
    linkedlist based on area and driver
    */
    if (command == "sort area" || command == "sort driver")
    {
        return true;
    }
    // if command is a valid driver name to possibly match with a driver obj
    else if (validateName(command))
    {
        return true;
    }
    // if command is a valid area to possibly match with a driver obj
    else if (validateNumber(command))
    {
        return true;
    }
    return false;
}

/*
the validateCoord function takes a string: the coordinate string from routes file.
It validates coords by dividing coords based on the comma separating them,
checking for digit, single decimal point (with at least 1 digit after),
hyphen before first digit if negative coordinate,
if the first coordinate is the same as the last,
and any missing coordinates
*/
bool validateCoord(string coordstring)
{
    // finds the first coord pair and stores to check with last coord pair later
    string sub = coordstring;
    string firstcoordpair = coordstring.substr(0, coordstring.find(" "));
    string lastcoordpair;
    string coordsub;

    // set a bool last to false to see if at last coord pair
    // if not: keep checking each coord pair for invalid
    bool last = false;
    while (!last)
    {
        /*
        if last coordinate pair (space index == -1)
        set coordsub to last pair (sub) and set last to true to end
        while loop which goes through each coord pair
        else: set coord pair to next coord pair by finding space inbetween
        */
        int spaceindex = sub.find(" ");
        if (spaceindex == -1)
        {
            coordsub = sub;
            lastcoordpair = coordsub;
            last = true;
        }
        else
        {
            coordsub = sub.substr(0, sub.find(" "));
        }

        /*
        separate x and y coord by comma index, check if
        missing x and y coord (since comma is at beginning or end index of
        the coord pair)
        if so: return false (invalid)
        */
        unsigned long int commaindex = coordsub.find(",");
        if (commaindex == 0 || commaindex == coordsub.length() - 1)
        {
            return false;
        }

        // separate x and y coord
        string xcoord = coordsub.substr(0, commaindex);
        string ycoord = coordsub.substr(commaindex + 1);

        /*
        calls validateNumber for both x and y coord
        to see if x and y are valid numbers: if either of them are not, return false
        */
        if (!validateNumber(xcoord) || !validateNumber(ycoord))
        {
            return false;
        }

        /*
        if at last coord pair, separate first and last coordpair into their x and y
        coordinates. Since both are valid (passed the validation stage), convert
        to doubles to check if their values are equal. If not, return false
        */
        if (last)
        {
            double xfirstpair = stod(firstcoordpair.substr(0, firstcoordpair.find(",")));
            double yfirstpair = stod(firstcoordpair.substr(firstcoordpair.find(",") + 1));

            if (xfirstpair != stod(xcoord) && yfirstpair != stod(ycoord))
            {
                return false;
            }
        }
        // remove the already checked coordpair from substring of coords to continue checking other pairs
        sub = sub.substr(spaceindex + 1);
    }
    // all validations have passed, return true
    return true;
}

/*
the validateName function takes a string: the name substring
(the substring from each line of the 1st file), and checks to see if each character
in the name is a valid character (alphanumeric, hyphen, apostrophe, single space).
If any character isn't valid, return false, else return true
*/
bool validateName(string name)
{
    // create an int to count the amount of spaces in the name
    int counter = 0;

    /*
    go through each character of the name to see if
    1. check if it is not a number and letter
    2. the character is not a hyphen or apostrophe
    3. if not, if there is a space, increase counter
    3. if does not meet these conditions, return false
    */
    for (unsigned long int i = 0; i < name.length(); i++)
    {
        if ((!isalpha(name[i]) && !isdigit(name[i])))
        {
            if (name.substr(i, 1) != "-" || name.substr(i, 1) != "`")
            {
                if (name[i] == ' ')
                {
                    counter++;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    /*if at least 2 spaces in the name, return false
    or the name has all valid characters, so return true*/
    if (counter >= 2)
    {
        return false;
    }
    return true;
}

/*
the validateNumber function takes a string: the "numbers" from the
coordinates string & command
and checks if the input is a number and specific criteria,
returns true if valid "number"
return false if invalid "number"
*/
bool validateNumber(string num)
{
    // checks if string is empty: if so, return false
    if (num.length() == 0)
    {
        return false;
    }

    /*
    go through the num string and see if each character is
    a hyphen that is at the beginning of the string,
    a decimal that only occurs once and not at the end of the "number",
    or a digit
    */
    for (unsigned long int i = 0; i < num.length(); i++)
    {
        /*
        checks if a character is a hyphen: if so, must be at beginning,
        so if the "number" is only a hyphen or not at beginning of number,
        return false
        */
        if (num[i] == '-')
        {
            if (num.length() == 1 || i != 0)
            {
                return false;
            }
        }
        /*
        checks if a character is a decimal: if so, cannot be at end (length-1)
        */
        else if (num[i] == '.')
        {
            if (i == num.length() - 1)
            {
                return false;
            }
            // checks if any character past decimal is another decimal, if so return false
            else
            {
                for (unsigned long int j = i + 1; j < num.length(); j++)
                {
                    if (num[j] == '.')
                    {
                        return false;
                    }
                }
            }
        }
        // checks if character is not a digit: if not a digit, return false
        else if (!isdigit(num[i]))
        {
            return false;
        }
    }
    /*
    return true if
    a hyphen that signifies a negative number
    a decimal that only occurs once and not at the end of the "number"
    or a digit
    */
    return true;
}
