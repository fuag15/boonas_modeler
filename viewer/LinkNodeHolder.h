#ifndef __LinkNodeHolder_h__
#define __LinkNodeHolder_h__
#include "LinkNode.h"

class LinkNodeHolder
{
    //Q_OBJECT

  public:
    LinkNodeHolder();
    ~LinkNodeHolder();
    void add(float x, float y, float z, float w);
    void reset(); // puts cursor at first node
    bool advance(); // advances cursor, true successfull
    bool hasCurent(); // true if there is a current
    bool hasNext(); //true if there is a next
    bool hasNextCursor(); //true if there is a next
    float getX();
    float getY();
    float getZ();
    float getW();
    void setX(float a);
    void setY(float a);
    void setZ(float a);
    void setW(float a);
    LinkNodeHolder* getNext();
    void setNext(LinkNodeHolder* newNext);
    LinkNode* getCurrent(); // returns a pointer to the current cursor
    LinkNodeHolder* next;
    LinkNode* start;
    LinkNode* end;
    LinkNode* cursor;
    LinkNode* temp;
};

#endif