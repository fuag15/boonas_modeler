#ifndef __LNHHolder_h__
#define __LNHHolder_h__
#include "LinkNodeHolder.h"

class LNHHolder // this is a holder of
{
    //Q_OBJECT

  public:
    LNHHolder(); // makes a cursor
    ~LNHHolder(); // deletes cursor
    void add(LinkNodeHolder* toAdd); // adds the LinkNodeHolder to the class
    void reset(); // puts cursor at first node
    bool advance(); // advances cursor, true successfull
    bool hasCurent(); // true if there is a current
    bool hasNext(); //true if there is a next
    bool isNotLast(); //true if this is not the last one
    LinkNodeHolder* getCurrent(); // returns a pointer to the current cursor
    LinkNodeHolder* start; // start of the list pointer
    LinkNodeHolder* end; // end of the list pointer (NOT USED)
    LinkNodeHolder* cursor; // end cursor
    LinkNodeHolder* temp; // temporary pointer for use in functions
};

#endif