// Matthew Rutigliano
// Stack class header file
// Purpose: The stack class has all attributes necessary to create a stack. Stacks are a
//          last in first out data structure, with the stack itself consisting of an array
//          sized to the user's specification.

class Stack
{
 public:
  
  Stack(int);
  // Default constructor
  // Precondition: User has specified size
  // Postcondition: Memory has been allocated, private attributes have been initialized
  
  ~Stack();
  // Destructor
  // Precondition: Stack has been initialized
  // Postcondition: Memory has been deallocated
  
  Stack(const Stack &);
  // Copy constructor
  // Precondition: One stack object has been initialized
  // Postcondition: A second stack object has been initialized, identical to the first
  
  Stack & operator=(const Stack &);
  // Overloaded assignment operator
  // Precondition: Two stack objects have been initialized
  // Postcondition: The first stack object is identical to the second

  bool push(int);
  // Integer is pushed onto the stack
  // Precondition: Stack has been initialized
  // Postcondition: Integer is now the top of the stack
  
  bool pop(int &);
  // Top of the stack is removed, with the passed in variable being set to it
  // Precondition: Stack has been initialized, at least one variable has been pushed
  // Postcondition: Passed in variable is now the popped value, top of the stack is the
  //                value below it
  
  int peek();
  // The value at the top of the stack is returned without popping it
  // Precondition: Stack has been initialized, at least one value has been pushed
  // Postcondtion: Top value has been returned, stack is unchanged
  
  bool isEmpty() const;
  // Returns true if stack is empty
  // Precondition: Stack has been initialized
  // Postcondition: None

 private:
  int *stackArray;
  // Stack itself
  
  int stackSize;
  // Size of stack array
  
  int top;
  // Array coordinate at the top
  
  void resize();
  // Resize function if stack goes over capacity
  // Precondition: Value has been pushed when stack is full
  // Postcondition: stackSize is doubled, with an array capacity to match
};
