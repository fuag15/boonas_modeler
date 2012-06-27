
//
// ============================================================
//
//                      FRAME.C
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
#include <strings.h>
#include <iostream>
#include "Frame.h"

#define		TRUE		1 
#define		FALSE		0


/*
   ==========================================================

	       CONSTRUCTORS, DESTRUCTOR

   ==========================================================
*/

Frame :: Frame ()

   {
      _u = Vector ( 1.0, 0.0, 0.0 ) ;
      _v = Vector ( 0.0, 1.0, 0.0 ) ;
      _w = Vector ( 0.0, 0.0, 1.0 ) ;
   }

Frame :: Frame ( const Vector& u, 
		 const Vector& v, 
		 const Vector& w, 
		 const Point& o )

   {
      _u = u ;
      _v = v ;
      _w = w ;
      _origin = o ;
   }

Frame :: Frame ( const Vector& w, 
		 const Vector& y, 
		 const Point& o )

		// This routine constructs a frame from two vectors.
		//  It sets the first vector to be w normalized.
		//  It sets u as the normalized cross product of y and w 
		//  It sets v as the normalized cross product of w and u 

   {
      _w = w ;
      _u = cross ( y, _w ) ;
      _v = cross ( _w, _u ) ;

      _u.normalize() ;
      _v.normalize() ;
      _w.normalize() ;

      _origin = o ;
   }

Frame :: Frame ( const Frame& f ) 

   {
      _u = f._u ;
      _v = f._v ;
      _w = f._w ;
      _origin = f._origin ;
   }

Frame :: ~Frame () { }
      

/*
   ==========================================================

	       OPERATOR=

   ==========================================================
*/

Frame& Frame :: operator= ( const Frame& f ) 

   {
      if ( this == &f ) return ( *this ) ;

      _u = f._u ;
      _v = f._v ;
      _w = f._w ;
      _origin = f._origin ;

      return ( *this ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& operator<< ( ostream& co, const Frame& f )

   {
      return f.output ( co ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& Frame :: output ( ostream& co, const int indent ) const 

   {
      for ( int k = 0 ; k < indent ; k++ ) co << " " ;

      co << "Frame ( " 
	 << _u << ", " 
	 << _v << ", " 
	 << _w << ", " 
	 << _origin << " )" << endl ;

      return ( co ) ;
   }

/*
   ==========================================================

	       COMPARISON OPERATIONS

   ==========================================================
*/

int operator== ( const Frame& f1, const Frame& f2 ) 

   {
      if ( ( f1._u == f2._u ) &&
           ( f1._v == f2._v ) &&
           ( f1._w == f2._w ) &&
           ( f1._origin == f2._origin ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

int operator!= ( const Frame& f1, const Frame& f2 ) 

   {
      if ( f1 == f2 )
	    return ( FALSE ) ;
	 else
	    return ( TRUE ) ;
   }

/*
   ==========================================================

	       NORMALIZE

   ==========================================================
*/

void Frame :: normalize ()  

   {
      _u.normalize() ;
      _v.normalize() ;
      _w.normalize() ;
   }
