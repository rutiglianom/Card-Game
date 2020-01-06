// Matthew Rutigliano
// Queue Class Header file
// Purpose: The Queue class has all the attributes necessary to create a queue. A queue
//          is a first in first out data structure of nodes. After being initialized,
//          the enqueue function is used to add a node to the queue, with dequeue removing
//          the first one queued.

class Queue
{
 public:
  
  Queue();
  // Default constructor
  // Precondition: None
  // Postcondition: Queue is ready to be added to
  
  ~Queue();
  // Destructor
  // Precondition: Queue has been initialized
  // Postcondition: Memory has been deallocated
  
  Queue(const Queue &);
  // Copy constructor
  // Precondition: One queue has been initialized
  // Postcondition: A second queue has been created, identical to the first
  
  Queue & operator=(const Queue &);
  // Overloaded assignment operator
  // Precondition: Two queues have been initialized
  // Postcondition: The first queue is now identical to the second

  bool enqueue(int);
  // Adds a node to the queue
  // Precondition: Queue has been initialized
  // Postcondition: Node is now at the back of the queue
  
  bool dequeue(int&);
  // Removes the front node from the queue
  // Precondition: At least one node has been queued
  // Postcondition: The queue has one less node, and the head is now the node behind the first
  
  int peek();
  // Returns the value of the front node without dequeuing it
  // Precondition: At least one value has been queued
  // Postcondition: Value has been returned
  
  bool isEmpty();
  // Returns true if queue is empty
  // Precondition: Queue has been initialized
  // Postcondition: Status of queue has been returned

 private:
  // Node structure
  struct Node
  {
    int value;
    Node *next;
  };

  // Pointer nodes to front and rear
  Node * front;
  Node * rear;

  // Number of nodes queued
  int numItems;
};
