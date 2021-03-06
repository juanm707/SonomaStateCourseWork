#include "LList.h"
LList::LNode::LNode ()
{ // This function will set value of data to 0 and value of next to NULL.
  data = 0;
  next = NULL;
}

LList::LList ()
{ // This function will set value of size to 0 and value of first to NULL.
  size = 0;
  first = NULL;
}

LList::LList (const LList & other)
{ // This function is the copy constructor and set value of size to 0, first to NULL and copy data of a list into another list.
  size = 0;
  first = NULL;

  LNode* np = other.first;
  
  while(np != NULL)
    {
      InsertLast(np->data);
      np = np->next;
    }
  
}

LList::~LList ()
{ // This function will delete the first item in the list

  if (first != NULL)
    {
      delete first;
    }
  
}

LList & LList::operator = (const LList & other)
{ // This function will check for self assignment.
  if (this == &other)
    {
      return * this;
    }

  if(first != NULL)
    {
      delete first;
    }

  LNode* np = other.first;

  while(np != NULL)
    {
      InsertLast(np->data);
      np = np->next;
    }

  return * this;
  
}

bool LList::operator == (const LList & other)
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

int LList::Size () const
{ // This function will return the value of size.
  return size;
}

ostream & operator << (ostream & outs, const LList & L)
{ // This function will travers the list, output the data values, and return outs.

  if (L.size == 0)
    {
      return outs;
    }
  
  LList::LNode* n = L.first;

  while (n != NULL)
    {
      outs << n->data;
      n = n->next;
      if (n != NULL)
	cout << ' ';
    }

  return outs;
}

bool LList::InsertFirst (const int & value)
{ // This function will allocate space for a new node. False if space cannot be allocated.
  // Set data of the new node to the input value, set the next of the new node to the current first.
  // Set the first of the list to the new node. Increment the size of the list, and return true.

  LNode* nw = new LNode;

  if (nw == NULL)
    {
      return false;
    }
  
  nw->data = value;
  nw->next = first;
  first = nw;
  size++;

  return true;
}

bool LList::InsertLast (const int & value)
{ // This function will insert a value at the end of list.

  if (size == 0)
    {
      return InsertFirst(value);
    }
  
  LNode* nw = new LNode;
  LNode* np = first;
  LNode* last = NULL;
  
  if (nw == NULL)
    {
      return false;
    }

  nw->data = value;
  nw->next = NULL;

  while (np != NULL)
    {
      last = np;
      np = np->next;
    }

  last->next = nw;
  size++;
  return true;
  
}

bool LList::DeleteFirst ()
{ // This function will delete the first value.

  if (size == 0)
    {
      return false;
    }

  LNode* temp = first;
  first = first->next;
  delete temp;
  size--;
  return true;
  
}

bool LList::DeleteLast ()
{ // This function will delete the last value.

  if (size == 0)
    {
      return false;
    }

  if (size == 1)
    {
      return DeleteFirst();
    }

  LNode* temp = first;
  LNode* secLast = NULL; 
  
  while (temp->next != NULL)
    {
      secLast = temp;
      temp = temp->next;
     
    }

  secLast->next = NULL;
  delete temp;
  size--;
  return true;
  
}

