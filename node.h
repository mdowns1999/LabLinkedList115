/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:
   //
   // Construct
   //
   //
   // Construct
   //

   Node() : data(T()), pNext(nullptr), pPrev(nullptr) {}

   Node(const T& data) : data(data), pNext(nullptr), pPrev(nullptr) {}

   Node(T&& data)
   {
      this->data = std::move(data);
      pNext = nullptr;
      pPrev = nullptr;
   }

   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource) 
{
   if (pSource != nullptr)
   {
      Node<T>* pDestination = new Node<T>(pSource->data);
      const Node<T>* pSrc = pSource;
      Node<T>* pDes = pDestination;

      for (const Node<T>* p = pSrc->pNext; p; p = p->pNext)
         pDes = insert(pDes, p->data, true);

      return pDestination;
   }
   else
      return nullptr;

}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   const Node<T>* pSrc = pSource;
   Node<T>* pDes = pDestination;
   Node<T>* pDesPrevious = pDes;

   while (pSrc != nullptr && pDes != nullptr)
   {
      pDesPrevious = pDes; // Update before anything becomes a nullptr
      pDes->data = pSrc->data;
      pDes = pDes->pNext;
      pSrc = pSrc->pNext;
   }

   //This will handle if the Source is bigger than the Destination
   if (pSrc != nullptr)
   {
      pDes = pDesPrevious; //Get the last pointer in PDes

      while (pSrc != nullptr)
      {
         pDes = insert(pDes, pSrc->data, true);
         if (pDestination == nullptr)
            pDestination = pDes;
         pSrc = pSrc->pNext; //Advance Source
      }
   }

   //This will handle if Destination is bigger than Source
   else if (pSrc == nullptr && pDes != nullptr)
   {
      bool setToNull = false;

      if (pDes->pPrev != nullptr)
         pDes->pPrev->pNext = nullptr;
      else
         setToNull = true;

      clear(pDes);

      if (setToNull)
         pDestination = nullptr;
   }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{
   std::swap(pLHS, pRHS);
}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove) 
{
   Node<T>* pReturn;

   if (pRemove == nullptr)
      return nullptr;

   if (pRemove->pPrev != nullptr)
      pRemove->pPrev->pNext = pRemove->pNext;
   if (pRemove->pNext != nullptr)
      pRemove->pNext->pPrev = pRemove->pPrev;

   if (pRemove->pPrev != nullptr)
      pReturn = pRemove->pPrev;
   else
      pReturn = pRemove->pNext;

   delete pRemove;

   return pReturn;
}


/**********************************************
 * INSERT 
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after = false)
{
   //Create a New Node
   Node<T>* pNew = new Node<T>(t);

   //Direct the new node to destination List
   if (pCurrent != nullptr && after == false)
   {
      pNew->pNext = pCurrent;
      pNew->pPrev = pCurrent->pPrev;
      pCurrent->pPrev = pNew;
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
   }
   if (pCurrent != nullptr && after == true)
   {
      pNew->pPrev = pCurrent;
      pNew->pNext = pCurrent->pNext;
      pCurrent->pNext = pNew;
      if (pNew->pNext)
         pNew->pNext->pPrev = pNew;
   }

   return pNew;
}

/******************************************************
 * SIZE
 * Find the size an unsorted linked list.  
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : number of nodes
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   size_t s = 0;

   for (const Node<T>* p = pHead; p; p = p->pNext)
      s += 1;
   return s;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   return out;
}

/*****************************************************
 * FREE DATA
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
   //Make a pointer to store the values we will delete
   Node<T>* pDelete;

   //While the structure still has nodes, delete
   while (pHead != nullptr)
   {
      pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
}


