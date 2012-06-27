//
// ============================================================
//
//                      VECTOR.C
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
#include "Vector.h"

#define		TRUE		1 
#define		FALSE		0


/*
   ==========================================================

	       CONSTRUCTORS, DESTRUCTOR

   ==========================================================
*/

Vector :: Vector ()

   {
      _vx = 0.0 ;
      _vy = 0.0 ;
      _vz = 0.0 ;
   }

Vector :: Vector ( const double x, const double y, const double z )

   {
      _vx = x ;
      _vy = y ;
      _vz = z ;
   }

Vector :: Vector ( const Vector& v ) 

   {
      _vx = v._vx ;
      _vy = v._vy ;
      _vz = v._vz ;
   }

Vector :: ~Vector () { }
      

/*
   ==========================================================

	       OPERATOR=

   ==========================================================
*/

Vector& Vector :: operator= ( const Vector& v ) 

   {
      if ( this == &v ) return ( *this ) ;

      _vx = v._vx ;
      _vy = v._vy ;
      _vz = v._vz ;

      return ( *this ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& operator<< ( ostream& co, const Vector& v )

   {
      co << "< "
	 << v._vx 
	 << ", "
	 << v._vy 
	 << ", "
	 << v._vz 
	 << " >" ;

      return co ;
   }

/*
   ==========================================================

	       COMPARISON OPERATIONS

   ==========================================================
*/

int operator== ( const Vector& v1, const Vector& v2 ) 

   {
      if ( ( v1._vx == v2._vx ) &&
           ( v1._vy == v2._vy ) &&
           ( v1._vz == v2._vz ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

int operator!= ( const Vector& v1, const Vector& v2 ) 

   {
      if ( ( v1._vx != v2._vx ) ||
           ( v1._vy != v2._vy ) ||
           ( v1._vz != v2._vz ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

/*
   ==========================================================

	       ARITHMETIC OPERATIONS

   ==========================================================
*/

Vector operator+ ( const Vector& v1, const Vector& v2 ) 

   {
      Vector vv ;

      vv._vx = v1._vx + v2._vx ;
      vv._vy = v1._vy + v2._vy ;
      vv._vz = v1._vz + v2._vz ;

      return ( vv ) ;
   }

Vector operator- ( const Vector& v1, const Vector& v2 ) 

   {
      Vector vv ;

      vv._vx = v1._vx - v2._vx ;
      vv._vy = v1._vy - v2._vy ;
      vv._vz = v1._vz - v2._vz ;

      return ( vv ) ;
   }

Vector operator- ( const Vector& v ) 

   {
      Vector vv ;

      vv._vx = - v._vx ;
      vv._vy = - v._vy ;
      vv._vz = - v._vz ;

      return ( vv ) ;
   }

Vector operator* ( const double& c, const Vector& v ) 

   {
      Vector vv ;

      vv._vx = c * v._vx ;
      vv._vy = c * v._vy ;
      vv._vz = c * v._vz ;

      return ( vv ) ;
   }

Vector operator* ( const Vector& v, const double& c ) 

   {
      Vector vv ;

      vv._vx = c * v._vx ;
      vv._vy = c * v._vy ;
      vv._vz = c * v._vz ;

      return ( vv ) ;
   }

Vector operator/ ( const Vector& v, const double& c ) 

   {
      Vector vv ;

      vv._vx = v._vx / c ;
      vv._vy = v._vy / c ;
      vv._vz = v._vz / c ;

      return ( vv ) ;
   }

Vector& Vector :: operator+= ( const Vector& v ) 

   {
      _vx += v._vx ;
      _vy += v._vy ;
      _vz += v._vz ;

      return *this ;
   }

Vector& Vector :: operator-= ( const Vector& v ) 

   {
      _vx -= v._vx ;
      _vy -= v._vy ;
      _vz -= v._vz ;

      return *this ;
   }

Vector& Vector :: operator*= ( const double& c ) 

   {
      _vx *= c ;
      _vy *= c ;
      _vz *= c ;

      return *this ;
   }

Vector& Vector :: operator/= ( const double& c ) 

   {
      _vx /= c ;
      _vy /= c ;
      _vz /= c ;

      return *this ;
   }

/*
   ==========================================================

	       NORMALIZE

   ==========================================================
*/

void Vector :: normalize ()  

   {
      double l =  length () ;

      _vx = _vx / l ;
      _vy = _vy / l ;
      _vz = _vz / l ;
   }

/*
   ==========================================================

	       LENGTH

   ==========================================================
*/

double Vector :: length ()  const

   {
      double		l ;

      l =  sqrt ( _vx * _vx + _vy * _vy + _vz * _vz ) ;
      return ( l ) ;
   }

/*
   ==========================================================

	       DOT

   ==========================================================
*/

double dot ( const Vector& v1, const Vector& v2 ) 

   {
      double		d ;

      d =  v1._vx * v2._vx + v1._vy * v2._vy + v1._vz * v2._vz ;

      return ( d ) ;
   }


/*
   ==========================================================

	       CROSS

   ==========================================================
*/

Vector cross ( const Vector& v1, const Vector& v2 ) 

   {
      Vector vv ;

      vv._vx = v1._vy * v2._vz - v1._vz * v2._vy ;
      vv._vy = - v1._vx * v2._vz + v1._vz * v2._vx ;
      vv._vz = v1._vx * v2._vy - v1._vy * v2._vx ;

      return ( vv ) ;
   }

