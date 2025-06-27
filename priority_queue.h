/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    Jenna Ray, Savanna WHittaker, Isabel Weaver
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h"

class TestPQueue;    // forward declaration for unit test class

namespace custom
{

/*************************************************
 * P QUEUE
 * Create a priority queue.
 *************************************************/
template<class T>
class priority_queue
{
   friend class ::TestPQueue; // give the unit test class access to the privates
   template <class TT>
   friend void swap(priority_queue<TT>& lhs, priority_queue<TT>& rhs);
public:

   //
   // construct
   //
   // default
   priority_queue()
   {
      container = 0;
   }
   // copy
   priority_queue(const priority_queue &  rhs)
   {
      container = rhs.container;
   }
   // move
   priority_queue(priority_queue && rhs)
   {
      container = std::move(rhs.container);
   }
   
   // range
   template <class Iterator>
   priority_queue(Iterator first, Iterator last) 
   {
      container.reserve(last - first);
      for(Iterator element = first; element != last; ++element)
      {
         container.push_back(*element);
      }
      
   }
   explicit priority_queue (custom::vector<T> && rhs) 
   {
      container = std::move(rhs);
      heapify();
   }
   explicit priority_queue (custom::vector<T>& rhs)
   {
      container = rhs;
      heapify();

   }
  ~priority_queue() {}

   //
   // Access
   //
   const T & top() const;

   //
   // Insert
   //
   void  push(const T& t);
   void  push(T&& t);     

   //
   // Remove
   //
   void  pop(); 

   //
   // Status
   //
   size_t size()  const 
   { 
      return container.size();
   }
   bool empty() const 
   { 
      return container.empty();
   }
   
private:

   void heapify();                            // convert the container in to a heap
   bool percolateDown(size_t indexHeap);      // fix heap from index down. This is a heap index!

   custom::vector<T> container; 

};

/************************************************
 * P QUEUE :: TOP
 * Get the maximum item from the heap: the top item.
 ***********************************************/
template <class T>
const T & priority_queue <T> :: top() const
{
   // check empty first
   if (container.empty())
      throw std::out_of_range("std:out_of_range");

   // return element in the front of the container
   return container.front();
}

/**********************************************
 * P QUEUE :: POP
 * Delete the top item from the heap.
 **********************************************/
template <class T>
void priority_queue<T>::pop()
{
    if (container.empty())
        return;

    // Swap first and last elements (0-based)
    std::swap(container[0], container[container.size() - 1]);
    
    // Remove the last element
    container.pop_back();
    
    // Percolate down the new root (using 1-based index)
    if (!container.empty())
        percolateDown(1);
}

/*****************************************
 * P QUEUE :: PUSH
 * Add a new element to the heap, reallocating as necessary
 ****************************************/
template <class T>
void priority_queue<T>::push(const T& t)
{
    container.push_back(t);
   
    // Percolate up from the last element
    size_t index = container.size();
    
    while (index > 1)
    {
        size_t parent = index / 2;
        if (container[parent - 1] < container[index - 1])
        {
            std::swap(container[parent - 1], container[index - 1]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

template <class T>
void priority_queue<T>::push(T&& t)
{
    container.push_back(std::move(t));
    // Percolate up from the last element
    size_t index = container.size();
    
    while (index > 1)
    {
        size_t parent = index / 2;
        if (container[parent - 1] < container[index - 1])
        {
            std::swap(container[parent - 1], container[index - 1]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

/************************************************
 * P QUEUE :: PERCOLATE DOWN
 * The item at the passed index may be out of heap
 * order. Take care of that little detail!
 * Return TRUE if anything changed.
 ************************************************/
template <class T>
bool priority_queue<T>::percolateDown(size_t indexHeap)
{
    // Convert to 0-based index for array access
    size_t index = indexHeap - 1;
    size_t size = container.size();
    
    if (index >= size) return false;

    size_t leftChild = 2 * index + 1;  // 0-based left child
    size_t rightChild = 2 * index + 2; // 0-based right child
    size_t largest = index;

    // Find the largest among parent and both children
    if (leftChild < size && container[largest] < container[leftChild])
        largest = leftChild;

    if (rightChild < size && container[largest] < container[rightChild])
        largest = rightChild;

    // If parent isn't largest, swap and continue
    if (largest != index)
    {
        std::swap(container[index], container[largest]);
        percolateDown(largest + 1); // Convert back to 1-based for recursion
        return true;
    }

    return false;
}

/************************************************
 * P QUEUE :: HEAPIFY
 * Turn the container into a heap.
 ************************************************/
template <class T>
void priority_queue<T>::heapify()
{
    if (container.empty()) return;
   
   size_t num = container.size();
   
   for (size_t indexHeap = num / 2; indexHeap >= 1; indexHeap--)
            percolateDown(indexHeap);
}

/************************************************
 * SWAP
 * Swap the contents of two priority queues
 ************************************************/
template <class T>
inline void swap(custom::priority_queue <T>& lhs,
                 custom::priority_queue <T>& rhs)
{
   std::swap(lhs.container, rhs.container); 
}

};

