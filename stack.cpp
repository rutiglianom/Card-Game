// Matthew Rutigliano
// Stack class implimentation file
// Purpose: Impliment stack class header file

#include "stack.h"
#ifndef STACK_H
#define STACK_H

// Constructor
Stack::Stack(int s)
{
  stackSize = s;
  stackArray = new int [stackSize];
  top = -1;
}

// Destructor
Stack::~Stack()
{
  delete [] stackArray;
}

// Copy Constructor
Stack::Stack(const Stack & intStack)
{
  stackSize = intStack.stackSize;
  stackArray = new int [stackSize];
  for (int i = 0; i < stackSize; i++)
    {
      stackArray[i] = intStack.stackArray[i];
    }
  top = intStack.top;
}

// Overloaded Assignment Operator
Stack& Stack::operator=(const Stack & intStack)
{
  if (this != &intStack)
    {
      delete [] stackArray;
      stackSize = intStack.stackSize;
      stackArray = new int [stackSize];
      for (int i = 0; i < stackSize; i++)
        {
          stackArray[i] = intStack.stackArray[i];
        }
      top = intStack.top;
    }
  return *this;
}

// resize
void Stack::resize()
{
  int * stackArray2 = new int [stackSize * 2];
  for (int i = 0; i < stackSize; i++)
    {
      stackArray2[i] = stackArray[i];
    }
  delete [] stackArray;
  stackArray = stackArray2;
  stackSize *= 2;
}

// push
bool Stack::push(int num)
{
  top++;
  if (top == stackSize)
    {
      resize();
    }
  stackArray[top] = num;
  return true;
}

// isEmpty
bool Stack::isEmpty() const
{
  return top == -1;
}

// pop
bool Stack::pop(int & val)
{
  if (!isEmpty())
    {
      val = stackArray[top];
      top--;
      return true;
    }
  else
    {
      return false;
    }
}

// peek
int Stack::peek()
{
  if (!isEmpty())
    {
      return stackArray[top];
    }
  else
    {
      return 0;
    }
  return 0;
}

#endif
