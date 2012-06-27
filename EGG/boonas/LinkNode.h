#ifndef __LinkNode_h__
#define __LinkNode_h__

class LinkNode
{
    //Q_OBJECT

  public:
    LinkNode(float x, float y, float z, float w);
    LinkNode* getNext();
    void setNext(LinkNode* newNext);
    void setID(float newID);
    float getRID();
    void setRID(float newRID);
    float getID();
    LinkNode* next;
    float xCord;
    float yCord;
    float zCord;
    float wCord;
    float imageID;
    float imageRID;
};

#endif