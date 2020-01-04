#include <galaxy-explorer/AsteroidList.hpp>

//Default constructor for the AsteroidListItem class
AsteroidListItem::AsteroidListItem() 
{
    this->next = NULL;
    this->data = NULL;
}

//Constructor that accepts an Asteroid input for the AsteroidListItem class
AsteroidListItem::AsteroidListItem(Asteroid a) 
{
    this->next = NULL;
    //Initialize the Asteroid with the Asteroid from the input
    this->data = new Asteroid (a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity());
}

//Destructor for the AsteroidListItem class
AsteroidListItem::~AsteroidListItem() 
{
    delete data; //Delete the asteroid pointed to by the node to avoid a memory leak
}

//Default constructor for class AsteroidList
AsteroidList::AsteroidList()
{
    AsteroidListItem* initial = NULL;
    head.setNext (initial); //Initialize next in head to point to NULL 
}

//Copy Constructor for class AsteroidList
AsteroidList::AsteroidList(const AsteroidList& src)
{
    (*this) = src; //Initializing the list on which the copy constructor was invoked from src using operator= function (implementation below in file)
}

//Destructor for class AsteroidList
AsteroidList::~AsteroidList() 
{
    clear (); //Delete every node in the list (clear () implementation below in file)
}

//Function to insert an AsteroidListItem node as the first node of an AsteroidList object
void AsteroidList::pushFront(Asteroid e) 
{
    AsteroidListItem* newptr = new AsteroidListItem (e); //New node to be inserted is initialized with the data from the input asteroid, e
    newptr->setNext(head.getNext()); //Make the new node to be inserted at the beginning point to the node that was previously the first node
    head.setNext(newptr); //Make next in head point to the inserted node
}

//Function to return the asteroid pointed to by the first AsteroidListItem node in the list
Asteroid& AsteroidList::front() 
{
    return ((head.getNext ())->getData ()); 
}

//Function to return the asteroid pointed to by the first AsteroidListItem node in the list
const Asteroid& AsteroidList::front() const 
{
    return ((head.getNext ())->getData ()); 
}

//Function to check if the list is empty
bool AsteroidList::isEmpty() const 
{
    //If the list is empty, return true
    if (head.getNext() == NULL)
	return true;
    
    //If the list is not empty, return false
    return false;
}

//Function to find the size of an AsteroidList object
int AsteroidList::size() const 
{
    const AsteroidListItem* ptr = head.getNext(); //Pointer initialized to the first node in the list
    int count = 0; //Counter to count number of nodes in list
    
    //Increment count as long as the list does not end
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->getNext(); //Increment ptr to point to the next node in the list
    }
    
    return count;  
}

//Function to return the address of the head of the list 
AsteroidListItem* AsteroidList::beforeBegin() 
{ 
    return &head;
}

//Function to return the address of the head of the list 
const AsteroidListItem* AsteroidList::beforeBegin() const 
{
    return &head;
}

//Function to return a pointer to the first AsteroidListItem node in the list
AsteroidListItem* AsteroidList::begin() 
{
    return (head.getNext ());
}

//Function to return a pointer to the first AsteroidListItem node in the list
const AsteroidListItem* AsteroidList::begin() const 
{
    return (head.getNext ());
}

//Function to return a pointer to the last AsteroidListItem in the list
AsteroidListItem* AsteroidList::beforeEnd()
{
    AsteroidListItem* ptr = head.getNext (); //Pointer initialized to point to the first AsteroidListItem node in the list    
    
    //As long as the node pointed to by ptr is not the last node, increment ptr 
    //to point to the next node in the list until it points to the last node
    while ((ptr->getNext ()) != NULL)
        ptr = ptr->getNext ();
    
    return ptr; 
}

//Function to return a pointer to the last AsteroidListItem in the list
const AsteroidListItem* AsteroidList::beforeEnd() const 
{
    const AsteroidListItem* ptr = head.getNext (); //Pointer initialized to point to the first AsteroidListItem node in the list    
    
    //As long as the node pointed to by ptr is not the last node, increment ptr 
    //to point to the next node in the list until it points to the last node
    while ((ptr->getNext ()) != NULL)
        ptr = ptr->getNext ();
    
    return ptr; 
}

//Function to return the position after the last AsteroidListItem node in the list
AsteroidListItem* AsteroidList::end() 
{
    return NULL;
}

//Function to return the position after the last AsteroidListItem node in the list
const AsteroidListItem* AsteroidList::end() const 
{
    return NULL;
}

//Function to insert a node after a certain node (pointed to by prev) in the list
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) 
{
    AsteroidListItem* tempptr = prev->getNext (); //Temporary pointer initialized to point to the node after the node pointed to by prev
    AsteroidListItem* newptr = new AsteroidListItem (e); //New pointer initialized to point to the new AsteroidListItem to be inserted, with data copied from Asteroid e
    
    prev->setNext (newptr); //Make the node pointed to by prev point to the new dynamically allocated node being inserted
    newptr->setNext (tempptr); //Make the inserted node point to the node that was previously pointed to by the node pointed to by prev

    return newptr; //Return a pointer to the inserted node
}

//Function to insert an AsteroidList object (called others) after a certain node (pointed to by prev) in another AsteroidList list
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) 
{
    //If the list to be inserted is empty, return a pointer to the node where the list was supposed be inserted
    if (((others.head).getNext ()) == NULL)
        return prev;
    
    const AsteroidListItem* ptr = (others.head).getNext(); //Pointer initialized to point to the first node in the list to be inserted
    AsteroidListItem* traverseptr = prev; //Pointer to traverse the list being inserted into is initialized to point to the node where the source list, others, will be inserted
    AsteroidListItem* concatempptr = traverseptr->getNext (); //Pointer to concatenate the list at the end of insertion initialized to point to the node where others will be inserted
    AsteroidListItem* newptr = NULL; //Pointer to point to the dynamically allocated nodes that are copies of the nodes in others

    //As long as others does not end, continue to copy nodes from it into the destination list
    while (ptr != NULL)
    {
        newptr = new AsteroidListItem (ptr->getData()); //newptr points to a dynamically allocated node initialized with the data from others
        traverseptr->setNext (newptr); //Make the node pointed to by traverseptr point to the dynamically allocated node that contains the data from the node in others
        
        ptr = ptr->getNext (); //Increment ptr to point to the next node in others
        traverseptr = traverseptr->getNext (); //Increment traverse ptr to point to latest node that was added to the destination list
    }
    
    AsteroidListItem* returnptr = head.getNext(); //Pointer to be returned is initialized to the first node in the destination list

    //Increment returnptr until it points to the latest node that was added to the destination list
    while ((returnptr->getNext ()) != NULL)
        returnptr = returnptr->getNext ();
    
    returnptr->setNext (concatempptr); //Concatenate the destination list by making the last added node point to the node pointed to be concatempptr
        
    return returnptr; //Return the pointer to the last added node
}

//Function to delete a node after a certain node in a list (pointed to by prev) 
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev)
{   
    AsteroidListItem* returnptr = (prev->getNext ())->getNext (); //Initialize the pointer to be returned to point to the node after the node that will be be deleted
    delete prev->getNext (); //Delete the node after the node pointed to by prev
    
    prev->setNext (returnptr); //Make the node pointed to by prev point to the node that was previously pointed to by the deleted node
    
    //If there was no node after the deleted node, return end ()
    if (returnptr == NULL)
        return end ();
    
    return returnptr; //If there was a node after the deleted node, return a pointer to it
}

//Function to delete an AsteroidList object
void AsteroidList::clear() 
{
    AsteroidListItem* ptr;
    
    //As long as the end of the list is not reached, continue to delete nodes in the list
    while((head.getNext()) != NULL) 
    {
         ptr = head.getNext (); //ptr points to the node at the beginning of the list at each iteration of the loop
         head.setNext (ptr->getNext()); //Increment next in head to point to the next node in the list
         
         delete ptr; //Delete the node pointed to by ptr
    }
    
    head.setNext (NULL); //After the list has no nodes, make next in head point to NULL
    
    return; 
}

//operator= function to set one AsteroidList object to be equal to another
AsteroidList& AsteroidList::operator=(const AsteroidList& src) 
{
    const AsteroidListItem* ptr = (src.head).getNext(); //Pointer to nodes in the list being copied from (src) initialized to the first node in src
    AsteroidListItem* last = NULL; //Pointer needed to point to the last node copied into
    AsteroidListItem* newptr = NULL; //Pointer needed to point to a dynamically allocated node to copy data from src
    
    clear (); //Delete the existing nodes in the destination list
     
    //Continue to copy nodes from the source list src as long as it does not end
    while(ptr != NULL) 
    {
        newptr = new AsteroidListItem ((ptr->getData())); //Pointer to a dynamically allocated node to copy data into
        
        //If the list being copied into is empty, make next in head point to 
        //the first dynamically allocated node with data copied from src's first node
        //If the list being copied into is not empty, make the node created in the last iteration 
        //of the loop point to the new node, copied from src, created in the current iteration
        if (last == NULL) 
            head.setNext (newptr);
        else 
            last->setNext (newptr);
        
        ptr = ptr->getNext (); //Increment ptr to point to the next node in the source list, src
        last = newptr; //Increment last to point to the last node copied into
    }
    
    return (*this);
}