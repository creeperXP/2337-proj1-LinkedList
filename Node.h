/*
Name: Nathan Han
netID: nxh230021
Date: 9/14/2024
The Node class defines single nodes for the LinkedList, containing a next pointer
and a driver object inside.
Methods include overloaded comparison operators to compare the drivers inside
the nodes, getting and setting the next node, getting the driver object inside 
the node, and overloaded << operator to print the driver object inside the node
*/
#ifndef NODE_H
#define NODE_H
#include <iostream>

template <typename T>
class Node
{
    public:
        //default constructor and overloaded constructor (with driver obj), initialize node with data, both sets next pointer to nullptr
        Node(){next=nullptr;}
        Node(T data){this->data=data; next=nullptr;}

        //retrieve driver obj from the node
        T getDriver() const {return data;}

        //retrieve and set next node which is used in LinkedList to link nodes together
        Node* getNextNode() const {return next;}
        void setNextNode(Node* next) {this->next=next;}

        //overloaded < > which calls the driver class overloaded < > to compare either area or driver names
        bool operator<(const Node&) const;
        bool operator>(const Node&) const;

        //overloaded << which calls driver class overloaded << to print driver data
        template <typename driverdata>
        friend std::ostream& operator<<(std::ostream& out, const Node<driverdata>& node);

        //destructor (not used in this case because drivers are not dynamically allocated)
        ~Node(){}



    private:
        T data;
        Node* next;
};

/*
Name: Nathan Han
netID: nxh230021
Date: 9/14/2024
Node class function definitions
*/

/*
the overloaded << operator allows printing of each node data
by calling the driver class overloaded << operator by
retrieving the driver object inside the node
Return the ostream& object to print out multiple nodes
in the linkedlist class
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node)
{
    out << node.data;
    return out;
}

/*
the overloaded > operator compares the implicit parameter
(left operand/driver) to the rightside driver.
This method calls the overloaded > operator in the Driver 
class and returns a bool depending on what the Driver static
variable is (1 = compare area, other = compare names)
ex: if left side area > right side area, then return true
*/
template <typename T>
bool Node<T>::operator>(const Node& node) const
{
   return data > node.data;
}

/*
the overloaded > operator compares the implicit parameter
(left operand/driver) to the rightside driver.
This method calls the overloaded > operator in the Driver 
class and returns a bool depending on what the Driver static
variable is (1 = compare area, other = compare names)
ex: if left side name < right side name, then return true
*/
template <typename T>
bool Node<T>::operator<(const Node& node) const
{
   return data < node.data;
}


#endif