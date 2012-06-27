#ifndef __LinkNodeHolder_h__
#define __LinkNodeHolder_h__
#include "LinkNode.h"
#include <QGLWidget>

class LinkNodeHolder
{
    //Q_OBJECT

  public:
    LinkNodeHolder();
    ~LinkNodeHolder();
    void add(float x, float y, float z, float w, float ID, bool bez);
    void addR(float ID, QString fn);
    void reset(); // puts cursor at first node
    bool advance(); // advances cursor, true successfull
    bool hasCurent(); // true if there is a current
    bool hasNext(); //true if there is a next
    bool hasNextCursor(); //true if there is a next
    void setBez(bool val);
    bool getBez();
    float getX();
    float getY();
    float getZ();
    float getW();
    void setX(float a);
    void setY(float a);
    void setZ(float a);
    void setW(float a);
    void setID(float a);
    void setName(QString fn);
    QString getName();
    float getID();
    void setRID(float a);
    float getRID();
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