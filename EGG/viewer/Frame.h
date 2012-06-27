#ifndef _FRAME_H
#define _FRAME_H

//
//  ============================================================
//
//                        Frame.h
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


#include "Vector.h"
#include "Point.h"
#include <iostream>
using namespace std;

class	Frame {

   private :
	
      Vector		_u, _v, _w ;
      Point		_origin ;

   public :

			//  Constructors

      Frame () ;

      Frame ( const Vector&, 
	      const Vector&,
	      const Vector&,
	      const Point& ) ;

      Frame ( const Vector&,
	      const Vector&,
	      const Point& ) ;

			//  Copy Constructor

      Frame ( const Frame& ) ;

			//  Destructor

      virtual ~Frame () ;

			//  Assignment

      Frame& operator= ( const Frame& ) ;

			//  Output and Input

      friend ostream& operator<< ( ostream&, const Frame& ) ;
      ostream& output ( ostream&, const int = 0 ) const ;

			//  Comparison

      friend int operator== ( const Frame&, const Frame& ) ;
      friend int operator!= ( const Frame&, const Frame& ) ;

			//  Member Functions

      void normalize () ;

			//  Access Functions

      Vector u () const { return _u ; } ;
      Vector v () const { return _v ; } ;
      Vector w () const { return _w ; } ;
      Point origin () const { return _origin ; } ;

      void set_origin ( const Point& p )
		{ _origin = p ; } ;

   } ;

const Frame CFrame ( VX, VY, VZ, PointZero ) ;
		     
#endif



