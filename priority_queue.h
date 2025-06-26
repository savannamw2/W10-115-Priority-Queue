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
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::pop()
   {
      if (container.empty())
         return;

      // Move the last element to the root
      container[0] = std::move(container.back());
      container.pop_back();

      // If there are still elements, percolate down from the root
      if (!container.empty())
         percolateDown(0);
   }

   /*****************************************
    * P QUEUE :: PUSH
    * Add a new element to the heap, reallocating as necessary
    ****************************************/
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::push(const T &t)
   {
      container.push_back(t);
      // Percolate up the new element
      size_t index = container.size() - 1;
      while (index > 0)
      {
         size_t parent = (index - 1) / 2;
         if (compare(container[parent], container[index]))
         {
            std::swap(container[parent], container[index]);
            index = parent;
         }
         else
            break;
      }
   }
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::push(T &&t)
   {
      container.push_back(std::move(t));
      // Percolate up the new element
      size_t index = container.size() - 1;
      while (index > 0)
      {
         size_t parent = (index - 1) / 2;
         if (compare(container[parent], container[index]))
         {
            std::swap(container[parent], container[index]);
            index = parent;
         }
         else
            break;
      }
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
      bool swapped = false;

      while (true)
      {
         size_t largest = indexHeap;
         size_t left = indexHeap * 2 + 1;  // Left child
         size_t right = indexHeap * 2 + 2; // Right child

         // Check if left child exists and is larger
         if (left < container.size() && compare(container[largest], container[left]))
            largest = left;

         // Check if right child exists and is larger
         if (right < container.size() && compare(container[largest], container[right]))
            largest = right;

         // If largest is still the parent, we're done
         if (largest == indexHeap)
            break;

         // Swap with the larger child
         std::swap(container[indexHeap], container[largest]);
         swapped = true;
         indexHeap = largest; // Move down to the child
      }

      return swapped;
   }

   /************************************************
    * P QUEUE :: HEAPIFY
    * Turn the container into a heap.
    ************************************************/
   template <class T, class Container, class Compare>
   void priority_queue<T, Container, Compare>::heapify()
   {
      for (size_t i = container.size() / 2; i > 0; --i)
      {
         percolateDown(i - 1); // Convert to 0-based indexing
      }
   }

   /************************************************
    * SWAP
    * Swap the contents of two priority queues
    ************************************************/
   template <class T, class Container, class Compare>
   inline void swap(custom::priority_queue<T, Container, Compare> &lhs,
                    custom::priority_queue<T, Container, Compare> &rhs)
   {
      using std::swap;
      swap(lhs.container, rhs.container);
      swap(lhs.compare, rhs.compare);
   }

};
