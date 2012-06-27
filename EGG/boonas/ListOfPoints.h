#ifndef LIST_OF_POINTS_H
#define LIST_OF_POINTS_H

//
//  ============================================================
//
//                  ListOfPoints
//
// ============================================================
//
//
//      Copyright (C) 1992,1993,1994,1995,1996
//
//                      Professor Kenneth I. Joy
//                      Computer Science Department
//                      University of California
//                      Davis, CA  95616
//
//      Permission is granted to use at your own risk and
//      distribute this software in source and binary forms
//      provided the above copyright notice and this paragraph
//      are preserved on all copies.  This software is provided
//      "as is" with no express or implied warranty.
//
//
//  ============================================================
//


#include "Point.h"
#include <iostream>
using namespace std;
class ListOfPoints {

   private :

		//  The list of points

      Point			*_list ;

		//  The actual length of the list

      int			_length ;

		//  The size of the allocated space for the list

      int			_size ;

		//  The amount of additional space to allocate when
		//     the list is full

      int			_chunk ;

   public :

		//  Constructors

      ListOfPoints () ;

      ListOfPoints ( Point*, const int ) ;

		//  Copy Constructor

      ListOfPoints ( const ListOfPoints& ) ;

		//  Destructor

      virtual ~ListOfPoints () ;

		//  Assignment

      ListOfPoints& operator= ( const ListOfPoints& ) ;

		//  Output -- for both referenced lists and pointers

      friend ostream& operator<< ( ostream&, const ListOfPoints& ) ;
      friend ostream& operator<< ( ostream&, const ListOfPoints * ) ;

		//  Indexing -- two operators for both the const
		//	and non-const instances

      Point& operator[] ( const int ) ;
      Point& operator[] ( const int ) const ;

		//  Sublists

      ListOfPoints operator() ( const int, const int ) ;

		//  Add a Point to the list

      void add ( const Point& ) ;

		//  Add a list of Points to the list 

      void add ( const ListOfPoints& ) ;

		//  Obtain the length of the list

      int length () const ;

		//  Calculate the point that is the average of
		//	add Points in the list

      Point average() const ;

   } ;

#endif


