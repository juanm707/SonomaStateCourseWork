#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class ST> class OrderedSet;
template <class ST> ostream & operator << (ostream & outs, const OrderedSet<ST> & L);

template <class ST>

class OrderedSet
{
   private:
      struct LNode
      {
         LNode ();
         ST data;
         LNode * next;
	 LNode * prev;
      };
  
   public:

  class Exception
  {
  public:
    Exception ();
    Exception (string msg);
    Exception (int idx);

    string Message () const;
  private:
    string message;
  };
  
  class Iterator
  {
  public:

    Iterator ();
    Iterator (LNode * NP);
    //const ST operator * () const;
    Iterator operator ++ ();
    ST & operator * () const;
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);
    bool operator == (const Iterator & other) const;
    bool operator != (const Iterator & other) const;
  private:
    LNode * current;
  };
  
      OrderedSet ();
      OrderedSet (const OrderedSet & other);
      ~OrderedSet ();
      OrderedSet & operator = (const OrderedSet & other);
      bool operator == (const OrderedSet & other);
      int Size () const;

  void SetDirection (dtype dir);
  dtype GetDirection () const;
  friend ostream & operator << <> (ostream & outs, const OrderedSet<ST> & L);
 
  void Forward (void function (const ST & param));
  void Backward (void function (const ST & param));

  void PrintValue (const int & value);

  Iterator begin () const;
  Iterator rbegin () const;
  Iterator end () const;
  Iterator rend () const;

  ST & operator [] (const int & index) const;

  void Clear ();
  bool IsEmpty () const;
  bool IsIn (const ST & value) const;
  bool Insert (const ST & value);
  bool Delete (const ST & value);
  OrderedSet operator + (const OrderedSet & other);
  OrderedSet operator * (const OrderedSet & other);
  
   private:
  
      bool InsertFirst (const ST & value);
      bool InsertLast (const ST & value);
      bool DeleteFirst ();
      bool DeleteLast ();
  
      LNode * first;
      LNode * last;
      int size;
      dtype direction;
      
};

//#include OrderedSet.h

template <class ST>
OrderedSet<ST>::LNode::LNode ()
{ // This function will set value of next to NULL.
 
  next = NULL;
  prev = NULL;
}

template <class ST>
OrderedSet<ST>::OrderedSet ()
{ // This function will set value of size to 0 and value of first to NULL.
  first = NULL;
  last = NULL;
  size = 0;
  direction = FORWARD;
}

template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
{ // This function is the copy constructor and set value of size to 0, first to NULL and copy data of a list into another list.
  size = 0;
  first = NULL;
  
  /*LNode* np = other.first;
  
  while(np != NULL)
    {
      InsertLast(np->data);
      np = np->next;
      }*/
  
  for (LNode * n = other.first; n != NULL; n = n->next)
    {
      InsertLast (n->data);
    }
  direction = other.direction;
  
}

template <class ST>
OrderedSet<ST>::~OrderedSet ()
{ // This function will delete the first item in the list

  while (first)
    {
      DeleteFirst();
    }
}

template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet<ST> & other)
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

template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet & other)
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

template <class ST>
int OrderedSet<ST>::Size () const
{ // This function will return the value of size.
  return size;
}

template <class ST>
void OrderedSet<ST>::SetDirection (dtype dir)
{
  direction = dir;
}

template <class ST>
dtype OrderedSet<ST>::GetDirection () const
{
  return direction;
}

template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & L)
{ // This function will traverse the list, output the data values, and return outs.

  if (L.first == NULL)
    return outs;
  
  if (L.direction == FORWARD)
    {//Print the list from beginning (first) to end
      outs << '{' << L.first->data;

      typename OrderedSet<ST>::LNode* n;
      for (n = L.first->next; n != NULL; n = n->next)
	outs << ',' << n->data;
      outs << '}';
    }
  
  else //L.direction == BACKWARD
    {//Print the list from end to beginning
      outs << '{' << L.last->data;

      typename OrderedSet<ST>::LNode* n;
      for (n = L.last->prev; n != NULL; n = n->prev)
	outs << ',' << n->data;
      outs << '}';
    }

  return outs;
  
}

template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
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

template <class ST>
bool OrderedSet<ST>::InsertLast (const ST & value)
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

template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
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

template <class ST>
bool OrderedSet<ST>::DeleteLast ()
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
  
  last = last->prev;
  last->next = NULL;
  temp->prev = NULL;
  
  delete temp;
  size--;
  return true;
  
}

template <class ST>
void OrderedSet<ST>::Forward (void function (const ST & param))
{
  for (LNode* n = first; n; n = n->next)
    function (n->data);

}


template <class ST>
void OrderedSet<ST>::Backward (void function (const ST & param))
{
  for (LNode * n = last; n; n = n->prev)
    function (n->data);
}

void PrintValue (const int & value)
{
  cout << "The value in the list is " << value << endl;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator ()
{
  current = NULL;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator (LNode * NP)
{
  current = NP;
}

/*template <class ST>
const ST OrderedSet<ST>::Iterator::operator * () const
{
  return current->data;
  }*/

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ ()
{
  if (current == NULL)
    throw(Exception("Cannot post-incremenet a NULL pointer"));
	  
  current = current->next;
  return *this;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ (int)
{
  Iterator temp = *this;
  if (current == NULL)
    throw(Exception("Cannot post-increment a NULL pointer"));
  
  current = current->next;
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- ()
{
  if (current == NULL)
    throw(Exception("Cannot pre-incremenet a NULL pointer"));
  
  current = current->prev;
  return *this;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- (int)
{
  Iterator temp = *this;
  if (current == NULL)
    throw(Exception("Cannot pre-incremenet a NULL pointer"));
	  
  current = current->prev;
  return temp;
}

template <class ST>
bool OrderedSet<ST>::Iterator::operator == (const Iterator & other) const
{
  return current == other.current;
}

template <class ST>
bool OrderedSet<ST>::Iterator::operator != (const Iterator & other) const
{
  return current != other.current;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin () const
{
  Iterator temp (first);
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin () const
{
  Iterator temp (last);
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end () const
{
  Iterator temp;
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend () const
{
  Iterator temp;
  return temp;
}

template <class ST>
ST & OrderedSet<ST>::operator [] (const int & index) const
{
  if (index < 0)
    throw(Exception(index));
  if (index >= size)
    throw(Exception(index));
  
  OrderedSet<ST>::LNode * n = first;

  for (int i = 0; i < index; i++)
    {
      n = n->next;
    }
  
  return n->data;
}

template <class ST>
ST & OrderedSet<ST>::Iterator::operator * () const
{
      if (current == NULL)
	{
	  throw(Exception("Cannot dereference a NULL pointer"));
	}
      return current->data;
  
}

template <class ST>
void OrderedSet<ST>::Clear ()
{ 
  while (0 < size)
    {
      DeleteFirst();
    }
  
}

template <class ST>
bool OrderedSet<ST>::IsEmpty () const
{
  if (size == 0)
    {
      return true;
    }

  return false;
}

template <class ST>
bool OrderedSet<ST>::IsIn (const ST & value) const
{
  LNode * nn = new LNode;
  if (nn == NULL)
    {
      return false;
    }
  nn->data = value;

  LNode * nx = first;

  while (nx != NULL)
    {
      if (nx->data == nn->data)
	{
	 return true;
	}
      nx = nx->next;
    }
  
  return false; 
}

template <class ST>
bool OrderedSet<ST>::Insert (const ST & value)
{
  
  if (size == 0)
    {
      return InsertFirst(value);
    }

  if (value < first->data)
    {
      return InsertFirst(value);
    }

  if (value > last->data)
    {
      return InsertLast(value);
    }
  

  if (IsIn(value))
    {
      return false;
    }

  LNode * nn = new LNode;
  if (nn == NULL)
    return false;
  nn->data = value;
  
  //Traverse the list
  LNode * nx = first;
  while (nx->data < value)
    {
      nx = nx->next;
    }

  LNode * pv = nx->prev;
  nn->prev = pv;
  nx->prev = nn;
  pv->next = nn;
  nn->next = nx;
  size++;
  return true;
  
}

template <class ST>
bool OrderedSet<ST>::Delete (const ST & value)
{
  if (size == 0)
    {
      return false;
    }

  if (size == 1)
    {
      return DeleteFirst();
    }

  if (first->data == value)
    {
      return DeleteFirst();
    }

  if (last->data == value)
    {
      return DeleteLast();
    }
  
  if (IsIn(value))
    {
      LNode * dl = new LNode;
      if (dl == NULL)
	{
	  return false;
	}

      dl->data = value;
      LNode * nx = first;
      while(nx->data != value)
	{
	  nx = nx->next;
	}
      LNode * pv = nx->prev;
      LNode * nextnext = nx->next;
      
      pv->next = nextnext;
      nextnext->prev = pv;
      size--;
      delete nx;
    }

  return false;
      
}

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator + (const OrderedSet & other)
{
  OrderedSet<ST> unionset;

  LNode * nd = first;
  LNode * of = other.first;

  while (nd != NULL || of != NULL)
    {
      if (nd!= NULL)
	{
      unionset.Insert(nd->data);
      nd = nd->next;
	}
      if (of != NULL)
	{
      unionset.Insert(of->data);
      of = of->next;
	}
    }
  return unionset;
  
  
}

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator * (const OrderedSet & other)
{
  OrderedSet<ST> interset;

  // LNode * t = first;
  LNode * o = other.first;

  while (o != NULL)
    {
      if (IsIn(o->data))
	{
	  interset.Insert(o->data);
	}
      o = o->next;
    }
  return interset;
  
}

template <class ST>
OrderedSet<ST>::Exception::Exception ()
{
}

template <class ST>
OrderedSet<ST>::Exception::Exception (string msg)
{
  message = msg;
}

template <class ST>
OrderedSet<ST>::Exception::Exception (int idx)
{
  stringstream ss (stringstream::in | stringstream::out);
  ss << "Subscript [" << idx << "] out of range";
  getline(ss, message);
}

template <class ST>
string OrderedSet<ST>::Exception::Message() const
{
  return message;
}




#endif

