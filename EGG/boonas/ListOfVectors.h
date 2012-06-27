#ifndef LIST_OF_VECTORS_H
#define LIST_OF_VECTORS_H

//
//  ============================================================
//
//                      ListOfVectors.h
//
//  ============================================================
//
//
// 	Copyright (C) 1992,1993,1994,1995,1996 
//
//			Professor Kenneth I. Joy
//			Computer Science Department
//			University of California
//			Davis, CA  95616
//
// 	Permission is granted to use at your own risk and 
//	distribute this software in source and binary forms 
//	provided the above copyright notice and this paragraph 
//	are preserved on all copies.  This software is provided 
//	"as is" with no express or implied warranty.
//
//
//  ============================================================
//
//

#include "Vector.h"
#include <iostream>
using namespace std;
class ListOfVectors {

   private :

      Vector			*_list ;

      int			_length ;
      int			_size ;
      int			_chunk ;

   public :

			//  Constructors

      ListOfVectors () ;

      ListOfVectors ( Vector*, const int ) ;

			//  Copy Constructor

      ListOfVectors ( const ListOfVectors& ) ;

			//  Destructor

      virtual ~ListOfVectors () ;

			//  Assignment

      ListOfVectors& operator= ( const ListOfVectors& ) ;

			//  Output

      friend ostream& operator<< ( ostream&, const ListOfVectors& ) ;
      friend ostream& operator<< ( ostream&, const ListOfVectors * ) ;

			//  Single Element access through indexing

      Vector& operator[] ( const int ) ;
      Vector& operator[] ( const int ) const ;

			//  Sublist generation

      ListOfVectors operator() ( const int, const int ) ;

			//  Add a vector to the list

      void add ( const Vector& ) ;

			//  Add a list to the end of another list

      void add ( const ListOfVectors& ) ;

			//  Length of the list

      int length () const ;

   } ;

#endif



