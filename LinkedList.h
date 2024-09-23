/*
Name: Nathan Han
netID: nxh230021
Date: 9/14/2024
The LinkedList templated class allows a singly linked list to be made with nodes of type T
(where T will be used as an driver type),
with functions including getting/setting head, tail pointers, 
using insertion sort (sortList()), and inserting a node of type T at the end of the linked list
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList 
{
    public:
    //default constructor: sets head and tail to nullptr
    LinkedList(){head=nullptr; tail=nullptr;}

    //mutator and accessor for head and tail
    Node<T>* getHead() const {return head;}
    Node<T>* getTail() const {return tail;}
    void setHead(Node<T>* head) {this->head = head;}
    void setTail(Node<T>* tail) {this->tail = tail;}

    //insert node of type T at end of linked list
    void insertNode(Node<T>*);

    //insertion sort in ascending order 
    //type T: used for driver objects only (so sort based on driver name or area)
    void sortList();

    //overloaded << operator that calls the node overloaded << to later print the driver object
    template <typename driverdata>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<driverdata>& list);

    //destructor to delete dynamically allocated nodes  
    ~LinkedList();

    
    private:
    //head and node tail of type T (will be used for type Driver)
        Node<T>* head;
        Node<T>* tail;
};

/*
Name: Nathan Han
netID: nxh230021
Date: 9/14/2024
LinkedList templated class function definitions
*/

/*
type T: will be used only for type Driver
the overloaded << operator allows printing of each node data inside
of the linked list.
While the current node is not null, print that node's driver,
go to the next node to print.
Return the ostream& object to write multiple node drivers to a 
print list statement
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
    Node<T>* current = list.head;
        while(current)
        {
            out << *current;
            current = current->getNextNode();
        }
    return out;
}

/*
type T: will be used only for type Driver
insert a new node at the end of the list.
If tail is null, set head and tail pointer to the inserted
node since it is the first node.
Else, point the original tail to the new node and set the tail
to the node passed in since the node is appended to the end
of the list
*/
template <typename T>
void LinkedList<T>::insertNode(Node<T>* node)
{
    if(!tail)
    {
        setHead(node);
        setTail(node);
    }
    else
    {
        tail->setNextNode(node);
        setTail(node);
    }
}

/*
type T: will be used only for type Driver
sort the linked list using
insertion sort, ascending order
*/
template <typename T>
void LinkedList<T>::sortList()
{
   //make a new head to append the sorted items to
   //make a current pointer to the original head to traverse through original list
   Node<T>* head_newlist = nullptr;
   Node<T>* current = head;

    //while there are still items in the linkedlist (not null)
    while (current)
    {
        //get the next node from the linked list
        Node<T>* next = current->getNextNode();  

        /*
        if there are no items in the newlist (denoted by the head of the newlist)
        or the driver data in the original list is less than the data in the head of the newlist,
        make current pointer point to 
        the previous head of the new list,
        put current at the head of the newlist
        */
        if (!head_newlist || *current < *head_newlist)
        {
            // Insert at the beginning of the new list
            current->setNextNode(head_newlist);
            head_newlist = current;
        }
        else
        {
            /*
            if current is not the smallest in newlist (the data inside: either name or area),
            find insertion point by going through new list and seeing if the driver
            is less than current
            */
            Node<T>* insert_point = head_newlist;
            while (insert_point->getNextNode() && *insert_point->getNextNode() < *current)
            {
                insert_point = insert_point->getNextNode();
            }
            /*
            When find smallest, set current next node to insert point next node
            and connect insert point pointer to current
            */
            current->setNextNode(insert_point->getNextNode());
            insert_point->setNextNode(current);
        }
        //go to next node in original list to find insertion point in new list for the next driver
        current = next;  
    }
    //set the head to the newlist head because the sorted nodes are connected to this head
    setHead(head_newlist);  
}

/*
type T: will be used only for type Driver
the linked list destructor goes through each node
and deletes the node, causing driver obj to be deleted
*/
template <typename T>
LinkedList<T>::~LinkedList()
{
    //set a current node and next node to go through the linked list to delete each node
    Node<T>* cur = head;
    Node<T>* next = nullptr;

    //while there are items in the list, save and delete the next node, then go to next node
    while (cur) {
        next = cur->getNextNode();
        delete cur;           
        cur = next;      
    }

    //make sure head and tail are reset to nullptr
    //do not point to anything to prevent access
    head = nullptr;
    tail = nullptr;
}

#endif