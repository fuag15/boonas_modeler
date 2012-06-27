#ifndef __LinkNode_h__
#define __LinkNode_h__

#include <QGLWidget>

class LinkNode
{
    //Q_OBJECT

  public:
    LinkNode(float x, float y, float z, float w, float ID, GLuint RID, bool bez);
    LinkNode* getNext();
    void setNext(LinkNode* newNext);
    void setID(float newID);
    float getRID();
    void setRID(GLuint newRID);
    float getID();
    LinkNode* next;
    float xCord;
    float yCord;
    float zCord;
    float wCord;
    float imageID;
    bool isBez;
    GLuint imageRID;
    QString imageName;
};

#endif