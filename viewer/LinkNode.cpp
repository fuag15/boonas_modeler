#include "LinkNode.h"

LinkNode::LinkNode(float x, float y, float z, float w)
{
    next = 0;
    xCord = x;
    yCord = y;
    zCord = z;
    wCord = w;
}

LinkNode* LinkNode::getNext()
{
    return next;
}

void LinkNode::setNext(LinkNode* newNext)
{
    next = newNext;
    
    return;
}
