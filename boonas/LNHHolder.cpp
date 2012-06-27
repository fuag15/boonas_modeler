#include "LNHHolder.h"

LNHHolder::LNHHolder() // initialize all values of pointers to null
{
    start = 0;
    end = 0;
    cursor = 0;
    temp = 0;
}

LNHHolder::~LNHHolder()
{
    cursor = start;
    while(cursor -> hasNextCursor() != 0) // while the cursor has more delete its opinter
    {
	temp = cursor;
	cursor = cursor -> getNext();
	delete temp;
    }
    
    if(cursor != 0) // only delete cursor if it exists, takes care of deleting an empty instance
    {
	delete cursor;
    }
    
    return;
}

bool LNHHolder::isNotLast() // returns true if the cursor is not last
{
    return (cursor -> hasNextCursor() != 0);
}

void LNHHolder::add(LinkNodeHolder* toAdd)
{
    if(start == 0) // if its the first instance special case
    {
	start = toAdd;
	end = start;
	cursor = start;
    }
    else // else add it and set cursor to current
    {
	cursor -> setNext(toAdd);
	cursor = cursor -> getNext();
	end = cursor;
    }
}

void LNHHolder::reset() // puts cursor at first node
{
    cursor = start;
}

bool LNHHolder::advance() // advances cursor, true successfull
{
    if(cursor -> getNext() != 0)
    {
	cursor = cursor -> getNext();
	return true;
    }
    return false;
}

bool LNHHolder::hasCurent() // true if there is a current
{
    if(cursor == 0)
    {
	return false;
    }
    return true;
}

bool LNHHolder::hasNext() //true if there is a next
{
    return (cursor -> getNext() != 0);
}

LinkNodeHolder* LNHHolder::getCurrent() // returns a *to the current cursor
{
    return cursor;
}