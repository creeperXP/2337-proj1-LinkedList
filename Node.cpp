/*
Node class function definitions (not used because Node is templated)
*/
/*
#include "Node.h"
#include <iostream>
*/
/*
the overloaded << operator allows printing of each node data
by calling the driver class overloaded << operator by
retrieving the driver object inside the node
Return the ostream& object to print out multiple nodes
in the linkedlist class
*/

/*
template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node)
{
    out << node.driver;
    return out;
}
*/

/*
the overloaded > operator compares the implicit parameter
(left operand/driver) to the rightside driver.
This method calls the overloaded > operator in the Driver 
class and returns a bool depending on what the Driver static
variable is (1 = compare area, other = compare names)
ex: if left side area > right side area, then return true
*/
/*
template <typename T>
bool Node<T>::operator>(const Node& node) const
{
   return driver > node.driver;
}
*/
/*
the overloaded > operator compares the implicit parameter
(left operand/driver) to the rightside driver.
This method calls the overloaded > operator in the Driver 
class and returns a bool depending on what the Driver static
variable is (1 = compare area, other = compare names)
ex: if left side name < right side name, then return true
*/
/*
template <typename T>
bool Node<T>::operator<(const Node& node) const
{
   return driver < node.driver;
}

*/
