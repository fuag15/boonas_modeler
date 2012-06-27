#ifndef LIST_OF_PROJPOINTS_H
#define LIST_OF_PROJPOINTS_H

//
//  ============================================================
//
//                  ListOfProjPoints
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

#include "ProjPoint.h"
#include <iostream>
using namespace std;
	//  This class represents a variable list or array of
	//	projective points.

class ListOfProjPoints {

   private :

		//  The list

      ProjPoint			*_list ;

		//  The length of the list

      int			_length ;

		//  The size of storage allocated for the list

      int			_size ;

		//  The amount that storage is increased upon 
		//	potential list overflow

      int			_chunk ;

   public :

		//  Constructors

      ListOfProjPoints () ;

      ListOfProjPoints ( ProjPoint*, const int ) ;

		//  Copy Constructor

      ListOfProjPoints ( const ListOfProjPoints& ) ;

		//  Destructor

      virtual ~ListOfProjPoints () ;

		//  Assignment

      ListOfProjPoints& operator= ( const ListOfProjPoints& ) ;

		//  Output -- for both references and pointers

      friend ostream& operator<< ( ostream&, const ListOfProjPoints& ) ;
      friend ostream& operator<< ( ostream&, const ListOfProjPoints * ) ;

		//  Indexing -- two function for both the const
		//	and non-const instances

      ProjPoint& operator[] ( const int ) ;
      ProjPoint& operator[] ( const int ) const ;

		//  Sublists

      ListOfProjPoints operator() ( const int, const int ) ;

		//  add an item to the end of the list

      void add ( const ProjPoint& ) ;

		//  add an list to the end of the list

      void add ( const ListOfProjPoints& ) ;

		//  obtain the length of the list

      int length () const ;

   } ;

#endif


