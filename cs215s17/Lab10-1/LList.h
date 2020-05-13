#ifndef LLIST_H
#define LLIST_H
#include <iostream>

using namespace std;

class LList
{
   private:
      struct LNode
      {
         LNode ();
         int data;
         LNode * next;
      };
   public:
      LList ();
      LList (const LList & other);
      ~LList ();
      LList & operator = (const LList & other);
      bool operator == (const LList & other);
      int Size () const;
      friend ostream & operator << (ostream & outs, const LList & L);
      bool InsertFirst (const int & value);
      bool InsertLast (const int & value);
      bool DeleteFirst ();
      bool DeleteLast ();
   private:
      LNode * first;
      LNode * last;
      int size;
};

#endif
