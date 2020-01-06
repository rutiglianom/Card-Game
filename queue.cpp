// Matthew Rutigliano
// Queue class implimentation file
// Purpose: Impliment queue class header file

#include "queue.h"
#ifndef QUEUE_H
#define QUEUE_H

// Constructor
Queue::Queue()
{
  front = nullptr;
  rear = nullptr;
  numItems = 0;
}

// Destructor
Queue::~Queue()
{
  Node * ptr;
  while (front != nullptr && rear != nullptr)
    {
      ptr = front;
      front = front->next;
      delete ptr;
    }
}

// Copy Constructor
Queue::Queue(const Queue &obj)
{
  numItems = obj.numItems;
  if (numItems != 0)
    {
      Node * ptr = obj.front;
      Node * newNode = new Node;
      newNode->value = ptr->value;
      newNode->next = nullptr;
      front = newNode;
      rear = newNode;
      ptr = ptr->next;
      while (ptr != nullptr)
        {
          enqueue(ptr->value);
          ptr = ptr->next;
        }
    }
  else
    {
      front = nullptr;
      rear = nullptr;
    }
}

// Overloaded Assignment Operator
Queue& Queue::operator=(const Queue & obj)
{
  if (this != &obj)
    {
      Node * ptr;
      while (front != nullptr && rear != nullptr)
        {
          ptr = front;
          front = front->next;
          delete front;
        }
  
      numItems = obj.numItems;
      if (numItems != 0)
        {
          ptr = obj.front;
          Node * newNode = new Node;
          newNode->value = ptr->value;
          front = newNode;
          rear = newNode;
          ptr = ptr->next;
          while (ptr != nullptr)
            {
              enqueue(ptr->value);
              ptr = ptr->next;
            }
        }
      else
        {
          front = nullptr;
          rear = nullptr;
        }
    }
  return *this;
}

// isEmpty
bool Queue::isEmpty()
{
  return front == nullptr;
}

// enqueue
bool Queue::enqueue(int num)
{
  Node * newNode = new Node;
  newNode->value = num;
  newNode->next = nullptr;
  if (isEmpty())
    {
      front = newNode;
      rear = newNode;
      newNode->next = nullptr;
    }
  else
    {
      rear->next = newNode;
      rear = newNode;
    }
  numItems++;
  return true;
}

// dequeue
bool Queue::dequeue(int & num)
{
  if (!isEmpty())
    {
      Node * ptr = front;
      num = ptr->value;
      front = front->next;
      delete ptr;
      numItems--;
      return true;
    }
  else
    {
      return false;
    }
}

// peek
int Queue::peek()
{
  if (!isEmpty())
    return front->value;
  else
    return 0;
}

#endif
