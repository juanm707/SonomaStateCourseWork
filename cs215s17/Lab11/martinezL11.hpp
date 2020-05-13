#ifndef LLIST2_HPP
#define LLIST2_HPP

#include <iostream>

using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class LT> class LList2;
template <class LT> ostream & operator << (ostream & outs, const LList2<LT> & L);

template <class LT>

class LList2
{
   private:
      struct LNode
      {
         LNode ();
	//void PrintNode (ostream & output);
         LT data;
         LNode * next;
	 LNode * prev;
      };
  
   public:
      LList2 ();
      LList2 (const LList2 & other);
      ~LList2 ();
      LList2 & operator = (const LList2 & other);
      bool operator == (const LList2 & other);
      int Size () const;

  void SetDirection (dtype dir);
  dtype GetDirection () const;
  friend ostream & operator << <> (ostream & outs, const LList2<LT> & L);
  
      bool InsertFirst (const LT & value);
      bool InsertLast (const LT & value);
      bool DeleteFirst ();
      bool DeleteLast ();

  void Forward (void function (const LT & param));
  void Backward (void function (const LT & param));

  void PrintValue (const int & value);
  
   private:
      LNode * first;
      LNode * last;
      int size;
      dtype direction;
      
};

//#include LList2.h

template <class LT>
LList2<LT>::LNode::LNode ()
{ // This function will set value of next to NULL.
 
  next = NULL;
  prev = NULL;
}

template <class LT>
LList2<LT>::LList2 ()
{ // This function will set value of size to 0 and value of first to NULL.
  first = NULL;
  last = NULL;
  size = 0;
  direction = FORWARD;
}

template <class LT>
LList2<LT>::LList2 (const LList2 & other)
{ // This function is the copy constructor and set value of size to 0, first to NULL and copy data of a list into another list.
  size = 0;
  first = NULL;
  
  for (LNode * n = other.first; n != NULL; n = n->next)
    {
      InsertLast (n->data);
    }
  direction = other.direction;
  
}

template <class LT>
LList2<LT>::~LList2 ()
{ // This function will delete the first item in the list

  while (first)
    {
      DeleteFirst();
    }
}

template <class LT>
LList2<LT> & LList2<LT>::operator = (const LList2<LT> & other)
{ // This function will check for self assignment.
  if (this == &other)
    {
      return * this;
    }

  while (first)
    {
      DeleteFirst();
    }
  for (LNode* n = other.first; n != NULL; n = n->next)
    {
      InsertLast(n->data);
    }
  direction = other.direction;
  return * this;
}

template <class LT>
bool LList2<LT>::operator == (const LList2 & other)
{ // This function will check for equality between two lists.
  if (size != other.size)
    {
      return false;
    }
  
  int i = 0;

  LNode* np = first;
  LNode* op = other.first;
  
  while (i < size)
    {
      if (np->data != op->data)
	{
	  return false;
	}

      np = np->next;
      op = op->next;

      i++;
    }

  return true;
  
}

template <class LT>
int LList2<LT>::Size () const
{ // This function will return the value of size.
  return size;
}

template <class LT>
void LList2<LT>::SetDirection (dtype dir)
{
  direction = dir;
}

template <class LT>
dtype LList2<LT>::GetDirection () const
{
  return direction;
}

template <class LT>
ostream & operator << (ostream & outs, const LList2<LT> & L)
{ // This function will traverse the list, output the data values, and return outs.

  if (L.first == NULL)
    return outs;
  
  if (L.direction == FORWARD)
    {//Print the list from beginning (first) to end
      outs << L.first->data;

      typename LList2<LT>::LNode* n;
      for (n = L.first->next; n != NULL; n = n->next)
	outs << ' ' << n->data;
    }
  
  else //L.direction == BACKWARD
    {//Print the list from end to beginning
      outs << L.last->data;

      typename LList2<LT>::LNode* n;
      for (n = L.last->prev; n != NULL; n = n->prev)
	outs << ' ' << n->data;
    }

  return outs;
  
}

template <class LT>
bool LList2<LT>::InsertFirst (const LT & value)
{ // This function will allocate space for a new node. False if space cannot be allocated.
  // Set data of the new node to the input value, set the next of the new node to the current first.
  // Set the first of the list to the new node. Increment the size of the list, and return true.

  LNode* nw = new LNode;

  if (nw == NULL)
    {
      return false;
    }

  if (size == 0)
    {
      nw->data = value;
      nw->next = NULL;
      nw->prev = NULL;
      first = nw;
      last = nw;
      size++;
      return true;
    }
  if (size >= 1)
    {
      nw->data = value;
      nw->next = first;
      nw->prev = NULL;
      first->prev = nw;
      
      first = nw;
      size++;
      return true;
    }
  
}

template <class LT>
bool LList2<LT>::InsertLast (const LT & value)
{ // This function will insert a value at the end of list.

  if (size == 0)
    {
      return InsertFirst(value);
    }
  
  LNode* nw = new LNode;
  
  if (nw == NULL)
    {
      return false;
    }

  if (size == 1)
    {
      nw->data = value;
      nw->next = NULL;
      nw->prev = last;
      //first stays same
      last->next = nw;
      last = nw;
      size++;
      return true;
    }
  
  nw->data = value;
  nw->next = NULL;
  nw->prev = last;
  
  last->next = nw;
  last = nw;
  size++;
  
  return true;
  
}

template <class LT>
bool LList2<LT>::DeleteFirst ()
{ // This function will delete the first value.

  if (size == 0)
    {
      return false;
    }

  
  if (size == 1)
    {
      LNode* temp = first;
      first = NULL;
      last = NULL;
      delete temp;
      size--;
      return true;
    }

  LNode* temp = first;
  first = first->next;
  first->prev = NULL;
  
  delete temp;
  size--;
  
  
  return true;
  
}

template <class LT>
bool LList2<LT>::DeleteLast ()
{ // This function will delete the last value.

  if (size == 0)
    {
      return false;
    }

  if (size == 1)
    {
      return DeleteFirst();
    }

  LNode* temp = last;
  
  /* while (temp->next != NULL)
    {
      secLast = temp;
      temp = temp->next;
     
    }

  secLast->next = NULL;
  */
  
  last = last->prev;
  last->next = NULL;
  temp->prev = NULL;
  
  delete temp;
  size--;
  return true;
  
}

template <class LT>
void LList2<LT>::Forward (void function (const LT & param))
{
  for (LNode* n = first; n; n = n->next)
    function (n->data);

}


template <class LT>
void LList2<LT>::Backward (void function (const LT & param))
{
  for (LNode * n = last; n; n = n->prev)
    function (n->data);
}

void PrintValue (const int & value)
{
  cout << "The value in the list is " << value << endl;
}

#endif

