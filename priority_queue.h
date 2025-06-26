/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h" // for default underlying container

class TestPQueue; // forward declaration for unit test class

namespace custom
{

   /*************************************************
    * P QUEUE
    * Create a priority queue.
    *************************************************/
   template <class T, class Container = custom::vector<T>, class Compare = std::less<T>>
   class priority_queue
   {
      friend class ::TestPQueue; // give the unit test class access to the privates
      template <class TT, class CContainer, class CCompare>
      friend void swap(priority_queue<TT, CContainer, CCompare> &lhs, priority_queue<TT, CContainer, CCompare> &rhs);

   public:
      //
      // construct
      //
      // default
      priority_queue(const Compare &c = Compare())
      {
         compare = c;
      }

      // copy
      priority_queue(const priority_queue &rhs, const Compare &c = Compare())
      {
         container = rhs.container;
         compare = c;
      }

      // move
      priority_queue(priority_queue &&rhs, const Compare &c = Compare())
      {
         container = std::move(rhs.container);
         compare = c;
      }

      template <class Iterator>

      // range
      priority_queue(Iterator first, Iterator last, const Compare &c = Compare())
      {
         compare = c;
         for (Iterator it = first; it != last; ++it)
            container.push_back(*it);
         heapify();
      }

      // move constructor to heap
      explicit priority_queue(const Compare &c, Container &&rhs)
      {
         compare = c;
         container = std::move(rhs);
         heapify();
      }

      // copy contructor to heap
      explicit priority_queue(const Compare &c, Container &rhs)
      {
         compare = c;
         container = rhs;
         heapify();
      }
      ~priority_queue()
      {
      }

      //
      // Access
      //
      const T &top() const;

      //
      // Insert
      //
      void push(const T &t);
      void push(T &&t);

      //
      // Remove
      //
      void pop();

      //
      // Status
      //
      size_t size() const
      {
         return container.size();
      }
      bool empty() const
      {
         return container.empty();
      }

   private:
      void heapify();                       // convert the container in to a heap
      bool percolateDown(size_t indexHeap); // fix heap from index down. This is a heap index!

      Container container; // underlying container (probably a vector)
      Compare compare;     // comparision operator
   };

   /************************************************
    * P QUEUE :: TOP
    * Get the maximum item from the heap: the top item.
    ***********************************************/
   template <class T, class Container, class Compare>
   const T &priority_queue<T, Container, Compare>::top() const
   {
      if (container.empty())
         throw std::out_of_range("std:out_of_range");
      return container.front();
   }

   /**********************************************
    * P QUEUE :: POP
    * Delete the top item from the heap.
    **********************************************/
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::pop()
   {
   }

   /*****************************************
    * P QUEUE :: PUSH
    * Add a new element to the heap, reallocating as necessary
    ****************************************/
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::push(const T &t)
   {
   }
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::push(T &&t)
   {
   }

   /************************************************
    * P QUEUE :: PERCOLATE DOWN
    * The item at the passed index may be out of heap
    * order. Take care of that little detail!
    * Return TRUE if anything changed.
    ************************************************/
   template <class T, class Container, class Compare>
   bool priority_queue<T, Container, Compare>::percolateDown(size_t indexHeap)
   {
      //make sure the index is valid
      if (indexHeap >= container.size())
      {
         return false; // nothing to do
      }
      //if the index is a leaf, nothing to do
      if (indexHeap * 2 >= container.size() || indexHeap * 2 + 1 >= container.size())
      {
         return false; // nothing to do
      }
      //find the left child and the right child of index
      size_t indexLeft = indexHeap * 2;
      size_t indexRight = indexLeft + 1;

      //find which child is bigger, the left child or the right child?
      size_t indexBigger = indexHeap;
      if (indexRight <= container.size() && container[indexLeft] < container[indexRight])
      {
         indexBigger = indexRight;
      }
      else
      {
         indexBigger = indexLeft;
      }
      
      //if the bigger child is greater than the parent, swap them
      if (container[indexHeap] < container[indexBigger])
      {
         //swap the parent and the bigger child
         auto temp = container[indexHeap];
         container[indexHeap] = container[indexBigger];
         container[indexBigger] = temp;
         //recursively call percolateDown on the bigger child
         return true;
      }
      else
      {
         return false;
      }
   }

   /************************************************
    * P QUEUE :: HEAPIFY
    * Turn the container into a heap.
    ************************************************/
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::heapify()
   {
   }

   /************************************************
    * SWAP
    * Swap the contents of two priority queues
    ************************************************/
   template <class T, class Container, class Compare>
   inline void swap(custom::priority_queue<T, Container, Compare> &lhs,
                    custom::priority_queue<T, Container, Compare> &rhs)
   {
   }

};
