#include "LinkNode.h"

LinkNode::LinkNode(float x, float y, float z, float w, float ID, GLuint RID, bool bez)
{
    next = 0;
    xCord = x;
    yCord = y;
    zCord = z;
    wCord = w;
    imageID = ID;
    imageRID = RID;
    imageName = "null";
    isBez = bez;
}

LinkNode* LinkNode::getNext()
{
    return next;
}

float LinkNode::getID()
{
	return imageID;
}

void LinkNode::setID(float newID)
{
	imageID = newID;
}

float LinkNode::getRID()
{
	return imageRID;
}

void LinkNode::setRID(GLuint newRID)
{
	imageRID = newRID;
}

void LinkNode::setNext(LinkNode* newNext)
{
    next = newNext;
    
    return;
}
