//
// ============================================================
//
//              ListOfProjPoints
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

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "ProjPoint.h"
#include "ListOfProjPoints.h"

#define		TRUE		1 
#define		FALSE		0

using namespace std;
/*
   ============================================================

		  CONSTRUCTOR, DESTRUCTOR
		     FOR LIST_OF_POINTS TYPES

   ============================================================
*/

ListOfProjPoints :: ListOfProjPoints ()

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;
   }

ListOfProjPoints :: ListOfProjPoints ( ProjPoint * v, const int n )

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < n ; i++ )
	 add ( v[i] ) ;
   }


ListOfProjPoints :: ListOfProjPoints ( const ListOfProjPoints& v )

   {
      _chunk = v._chunk ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < v._length ; i++ ) 
	 add ( v._list[i] ) ;
   }


ListOfProjPoints :: ~ListOfProjPoints () 

   {
      if ( _size > 0 ) {
	 delete [] _list ;
	 }

      _size = 0 ;
      _length = 0 ;
      _chunk = 0 ;
   }

/*
   ============================================================

		  OPERATOR=

   ============================================================
*/

ListOfProjPoints& ListOfProjPoints :: operator= ( const ListOfProjPoints& v )

   {
      if ( &v == this ) return ( *this ) ;

      _chunk = v._chunk ;

      if ( _size > 0 ) {
	 delete [] _list ;
	 }

      _size = 0 ;
      _length = 0 ;

      for ( int i = 0 ; i < v._length ; i++ )
	 add ( v._list[i] ) ;

      return ( *this ) ;
   }


/*
   ============================================================

		  OPERATOR[]

   ============================================================
*/

ProjPoint& ListOfProjPoints :: operator[] ( const int n ) const

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfProjPoints array index ["
	      << n
	      << "] is out of bounds [0,"
	      << _length - 1 << "]"
	      << endl << endl ;
	 exit ( 200 ) ;
	 }

      return ( _list[n] ) ;
   }

      
/*
   ============================================================

		  OPERATOR[]

   ============================================================
*/

ProjPoint& ListOfProjPoints :: operator[] ( const int n ) 

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfProjPoints array index ["
	      << n
	      << "] is out of bounds [0,"
	      << _length - 1 << "]"
	      << endl << endl ;
	 exit ( 200 ) ;
	 }

      return ( _list[n] ) ;
   }

/*
   ============================================================

		  ADD

   ============================================================
*/

void ListOfProjPoints :: add ( const ProjPoint& v )

   {
      if ( _length >= _size ) {
	 _size += _chunk ;
	 ProjPoint *vv = new ProjPoint[_size] ;
	 for ( int i = 0 ; i < _length ; i++ )
	    vv[i] = _list[i] ;
	 if ( _length > 0 ) {
	    delete [] _list ;
	    }
	 _list = vv ;
	 }

      _list[_length] = v ;
      _length++ ;
   }

void ListOfProjPoints :: add ( const ListOfProjPoints& e )

   {
      int n = e._length ;

      for ( int i = 0 ; i < n ; i++ ) {
	 add ( e[i] ) ;
	 }
   }

/*
   =============================================================

	       OPERATOR()

   =============================================================
*/

ListOfProjPoints ListOfProjPoints :: operator() ( const int first, 
					     const int second ) 

   {
      ListOfProjPoints v ;

      for ( int i = first ; i < second ; i++ )
	 v.add ( _list[i] ) ;

      return ( v ) ;
   }

/*
   =============================================================

	       OUTPUT

   =============================================================
*/

ostream& operator<< ( ostream& co, const ListOfProjPoints& plist ) 

   {
      co << "( " ;

      if ( plist._length > 0 ) co << plist._list[0] ;

      for ( int i = 1 ; i < plist._length ; i++ ) {
	 co << ", " << plist._list[i] ;
	 }

      co << " )" << endl ;

      return co ;
   }

/*
   ============================================================

                LENGTH

   ============================================================
*/


int ListOfProjPoints :: length () const
   
   {
      return ( _length ) ;
   }
