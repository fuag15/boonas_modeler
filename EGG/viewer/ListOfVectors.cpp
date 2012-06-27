//
// ============================================================
//
//              ListOfVectors
//
// ============================================================
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

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <strings.h>
#include "Vector.h"
#include "ListOfVectors.h"

#define		TRUE		1 
#define		FALSE		0

using namespace std;
/*
   ============================================================

		  CONSTRUCTOR, DESTRUCTOR
		     FOR LIST_OF_POINTS TYPES

   ============================================================
*/

ListOfVectors :: ListOfVectors ()

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;
   }

ListOfVectors :: ListOfVectors ( Vector * v, const int n )

   {
      _chunk = 64 ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < n ; i++ )
	 add ( v[i] ) ;
   }


ListOfVectors :: ListOfVectors ( const ListOfVectors& v )

   {
      _chunk = v._chunk ;
      _length = 0 ;
      _size = 0 ;

      for ( int i = 0 ; i < v._length ; i++ ) 
	 add ( v._list[i] ) ;
   }


ListOfVectors :: ~ListOfVectors () 

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

ListOfVectors& ListOfVectors :: operator= ( const ListOfVectors& v )

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

Vector& ListOfVectors :: operator[] ( const int n ) const

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfVectors array index ["
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

Vector& ListOfVectors :: operator[] ( const int n ) 

   {
      if ( ( n < 0 ) || ( n >= _length ) ) {
	 cerr << "ListOfVectors array index ["
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

void ListOfVectors :: add ( const Vector& v )

   {
      if ( _length >= _size ) {
	 _size += _chunk ;
	 Vector *vv = new Vector[_size] ;
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

void ListOfVectors :: add ( const ListOfVectors& e )

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

ListOfVectors ListOfVectors :: operator() ( const int first, 
					     const int second ) 

   {
      ListOfVectors v ;

      for ( int i = first ; i < second ; i++ )
	 v.add ( _list[i] ) ;

      return ( v ) ;
   }

/*
   =============================================================

	       OUTPUT

   =============================================================
*/

ostream& operator<< ( ostream& co, const ListOfVectors& plist ) 

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


int ListOfVectors :: length () const
   
   {
      return ( _length ) ;
   }

