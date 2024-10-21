/*
The Node class is templated.
It defines single nodes for the LinkedList, containing a next pointer
and a undefined type T object inside (which will have a Driver object).
Methods include overloaded comparison operators to compare the object inside
the nodes, getting and setting the next node, getting the object inside 
the node, and overloaded << operator to print the object inside the node
*/
#ifndef NODE_H
#define NODE_H
#include <iostream>

template <typename T>
class Node
{
    public:
        //default constructor and overloaded constructor (with type T), initialize node with data, both sets next pointer to nullptr
        //T will be Driver object
        Node(){next=nullptr;}
        Node(T data){this->data=data; next=nullptr;}

        //retrieve T/driver obj from the node
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
        ~Node(){};

    private:
    //next node and data of type T (used to store driver)
        T data;
        Node* next;
};

/*
type T: will be used only for type Driver
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
type T: will be used only for type Driver
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
type T: will be used only for type Driver
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
