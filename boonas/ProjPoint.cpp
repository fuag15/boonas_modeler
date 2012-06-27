//
// ============================================================
//
//                      PROJPOINT.C
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
#include "ProjPoint.h"

#define		TRUE		1 
#define		FALSE		0

using namespace std;
/*
   ==========================================================

	       CONSTRUCTORS, DESTRUCTOR

   ==========================================================
*/

ProjPoint :: ProjPoint ()

   {
      _x = 0.0 ;
      _y = 0.0 ;
      _z = 0.0 ;
      _w = 1.0 ;
   }

ProjPoint :: ProjPoint ( const double x, 
			 const double y, 
			 const double z, 
			 const double w )

   {
      _x = x ;
      _y = y ;
      _z = z ;
      _w = w ;
   }

ProjPoint :: ProjPoint ( const Point& p ) 

   {
      _x = p.x() ;
      _y = p.y() ;
      _z = p.z() ;
      _w = 1.0 ;
   }

ProjPoint :: ProjPoint ( const ProjPoint& p ) 

   {
      _x = p._x ;
      _y = p._y ;
      _z = p._z ;
      _w = p._w ;
   }

ProjPoint :: ~ProjPoint () { }
      

/*
   ==========================================================

	       OPERATOR=

   ==========================================================
*/

ProjPoint& ProjPoint :: operator= ( const ProjPoint& p ) 

   {
      if ( this == &p ) return ( *this ) ;

      _x = p._x ;
      _y = p._y ;
      _z = p._z ;
      _w = p._w ;

      return ( *this ) ;
   }

ProjPoint& ProjPoint :: operator= ( const Point& p ) 

   {
      _x = p.x() ;
      _y = p.y() ;
      _z = p.z() ;
      _w = 1.0 ;

      return ( *this ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& operator<< ( ostream& co, const ProjPoint& p )

   {
      co << "( "
	 << p._x 
	 << ", "
	 << p._y 
	 << ", "
	 << p._z 
	 << ", "
	 << p._w 
	 << " )" ;

      return co ;
   }

/*
   ==========================================================

	       COMPARISON OPERATIONS

   ==========================================================
*/

int operator== ( const ProjPoint& p1, const ProjPoint& p2 ) 

   {
      double x1 = p1._x / p1._w ;
      double y1 = p1._y / p1._w ;
      double z1 = p1._z / p1._w ;

      double x2 = p2._x / p2._w ;
      double y2 = p2._y / p2._w ;
      double z2 = p2._z / p2._w ;

      if ( ( x1 == x2 ) &&
           ( y1 == y2 ) &&
           ( z1 == z2 ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

int operator!= ( const ProjPoint& p1, const ProjPoint& p2 ) 

   {
      if ( p1._x == p2._x ) 
	    return ( FALSE ) ;
	 else
	    return ( TRUE ) ;
   }

/*
   ==========================================================

	       ARITHMETIC OPERATIONS

   ==========================================================
*/

ProjPoint operator- ( const ProjPoint& p )

   {
      return ( ProjPoint ( -p._x, -p._y, -p._z, -p._w ) ) ;
   }
   
/*
   ==========================================================

	       AFFINE

   ==========================================================
*/

ProjPoint affine ( const ProjPoint& p1, const ProjPoint& p2, const double t ) 

   {
      ProjPoint p ;

      p._x = p1._x + t * ( p2._x - p1._x ) ;
      p._y = p1._y + t * ( p2._y - p1._y ) ;
      p._z = p1._z + t * ( p2._z - p1._z ) ;
      p._w = p1._w + t * ( p2._w - p1._w ) ;

      return ( p ) ;
   }

ProjPoint affine ( const ProjPoint& p1, 
	       const ProjPoint& p2, 
	       const ProjPoint& p3, 
	       const double a1,
	       const double a2,
	       const double a3 )

   {
      ProjPoint p ;

      p._x = a1 * p1._x + a2 * p2._x + a3 * p3._x ;
      p._y = a1 * p1._y + a2 * p2._y + a3 * p3._y ;
      p._z = a1 * p1._z + a2 * p2._z + a3 * p3._z ;
      p._w = a1 * p1._w + a2 * p2._w + a3 * p3._w ;

      return ( p ) ;
   }

   
/*
   ==========================================================

	       PROJECT

   ==========================================================
*/

Point ProjPoint :: project() const 

   {
      if ( _w == 0 ) {
	 cerr << "Cannot project a point with projective "
	      << "coordinate zero -- " << *this ;
	 exit ( 200 ) ;
	 }

      return ( Point ( _x / _w, _y / _w, _z / _w ) ) ;
   }
