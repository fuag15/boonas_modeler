//
//  ============================================================
//
//              	ListOfPoints
//
//  ============================================================
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
#include "Point.h"
#include "ListOfPoints.h"

#define		TRUE		1 
#define		FALSE		0

using namespace std;

/*
   ============================================================

		  CONSTRUCTOR, DESTRUCTOR
		     FOR LIST_OF_POINTS TYPES

   ============================================================
*/

ListOfPoints :: ListOfPoints ()

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;
   }

ListOfPoints :: ListOfPoints ( Point * v, const int n )

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < n ; i++ )
	 add ( v[i] ) ;
   }


ListOfPoints :: ListOfPoints ( const ListOfPoints& v )

   {
      _chunk = v._chunk ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < v._length ; i++ ) 
	 add ( v._list[i] ) ;
   }


ListOfPoints :: ~ListOfPoints () 

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

ListOfPoints& ListOfPoints :: operator= ( const ListOfPoints& v )

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

Point& ListOfPoints :: operator[] ( const int n ) const

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfPoints array index ["
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

Point& ListOfPoints :: operator[] ( const int n ) 

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfPoints array index ["
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

void ListOfPoints :: add ( const Point& v )

   {
      if ( _length >= _size ) {
	 _size += _chunk ;
	 Point *vv = new Point[_size] ;
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

void ListOfPoints :: add ( const ListOfPoints& e )

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

ListOfPoints ListOfPoints :: operator() ( const int first, 
					     const int second ) 

   {
      ListOfPoints v ;

      for ( int i = first ; i < second ; i++ )
	 v.add ( _list[i] ) ;

      return ( v ) ;
   }

/*
   =============================================================

	       OUTPUT

   =============================================================
*/

ostream& operator<< ( ostream& co, const ListOfPoints& plist ) 

   {
      co << "( " ;

      if ( plist._length > 0 ) co << plist._list[0] ;

      for ( int i = 1 ; i < plist._length ; i++ ) {
	 co << ", " << plist._list[i] ;
	 }

      co << " )" ;

      return co ;
   }

ostream& operator<< ( ostream& co, const ListOfPoints *plist )

   {
      co << *plist ;
      return ( co ) ;
   }

/*
   ============================================================

                LENGTH

   ============================================================
*/


int ListOfPoints :: length () const
   
   {
      return ( _length ) ;
   }

/*
   ==========================================================

	       Average

   ==========================================================
*/

Point ListOfPoints :: average () const

   {
      int n = _length ;
      double fraction = 1.0 / double ( n ) ;

      double xx = 0.0 ;
      double yy = 0.0 ;
      double zz = 0.0 ;

      for ( int i = 0 ; i < n ; i++ ) {
	 xx += fraction * _list[i].x() ;
	 yy += fraction * _list[i].y() ;
	 zz += fraction * _list[i].z() ;
	 }

      return ( Point ( xx, yy, zz ) ) ;
   }


