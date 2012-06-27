#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

//
//  ============================================================
//
//                  Transformation
//
// ============================================================
//
//
//      Copyright (C) 1997
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

#include "Vector.h"
#include "ListOfVectors.h"
#include "Point.h"
#include "ListOfPoints.h"
#include "ProjPoint.h"
#include "ListOfProjPoints.h"
#include "Frame.h"
#include <iostream>
using namespace std;
		//  This class represents a set of transformations
		// 	in three-dimensional space and 4-dimensional
		//	projective space, which are implemented as
		//	a set of 4x4 matrices

class	Transformation {

   private :

		//  The 4x4 matrix representing the transformation

      double		_matrix[4][4] ;

		//  A private function that sets up an identity
		//	matrix

      void id () ;

   public :

		// Constructors

      Transformation () ;

		// Copy Constructors

      Transformation ( const Transformation& ) ;

		// Destructor

      virtual ~Transformation () ;

		// Assignment

      Transformation& operator= ( const Transformation& ) ;

		// Comparison

      friend int operator== ( const Transformation&, const Transformation& ) ;
      friend int operator!= ( const Transformation&, const Transformation& ) ;

		// Output

      friend ostream& operator<< ( ostream&, const Transformation& ) ;

		// Arithmetic Operations

      friend Transformation operator+ ( const Transformation&, const Transformation& ) ;
      friend Transformation operator- ( const Transformation&, const Transformation& ) ;
      friend Transformation operator- ( const Transformation& ) ;
      friend Transformation operator* ( const double, const Transformation& ) ;
      friend Transformation operator* ( const Transformation&, const double ) ;
      friend Transformation operator* ( const Transformation&, const Transformation& ) ;

      Transformation operator+= ( const Transformation& ) ;
      Transformation operator-= ( const Transformation& ) ;
      Transformation operator*= ( const Transformation& ) ;

		//  The following produce
		//   specific elementary transformations

      friend Transformation identity () ;
      friend Transformation translate_by (  const double, const double = 0.0, const double = 0.0 ) ;
      friend Transformation translate_by ( const Vector ) ;

      friend Transformation scale_by (  const double, const double = 1.0, const double = 1.0 ) ;
      friend Transformation scale_by ( const Vector ) ;

      friend Transformation x_rotate_by ( const double ) ;

      friend Transformation y_rotate_by ( const double ) ;

      friend Transformation z_rotate_by ( const double ) ;

      friend Transformation rotate_by ( const double, const Vector& ) ;

      friend Transformation frame_to_frame ( const Frame&, const Frame& ) ;


      friend Transformation view ( const double, const double, const double ) ;

      friend Transformation inverse_view ( const double, const double, const double ) ;

		//  Applying the Transformations to Vector Types

      Vector applied_to ( const Vector& ) const ;

		//  Applying the Transformations to ListOfVectors Types

      ListOfVectors applied_to ( const ListOfVectors& ) const ;

		//  Applying the Transformations to Point Types

      Point applied_to ( const Point& ) const ;

		//  Applying the Transformations to ListOfPoint Types

      ListOfPoints applied_to ( const ListOfPoints& ) const ;

		//  Applying the Transformations to ProjPoint Types

      ProjPoint applied_to ( const ProjPoint& ) const ;

		//  Applying the Transformations to ListOfProjPoint Types

      ListOfProjPoints applied_to ( const ListOfProjPoints& ) const ;

		//  return an item from the matrix that
		// 	represents this transformation

      double matrix ( const int, const int ) const ;

   } ;

       Transformation identity () ;
       Transformation translate_by (  const double, const double, const double) ;
       Transformation translate_by ( const Vector ) ;

       Transformation scale_by (  const double, const double, const double) ;
       Transformation scale_by ( const Vector ) ;

       Transformation x_rotate_by ( const double ) ;

       Transformation y_rotate_by ( const double ) ;

       Transformation z_rotate_by ( const double ) ;

       Transformation rotate_by ( const double, const Vector& ) ;

       Transformation view ( const double, const double, const double ) ;

       Transformation inverse_view ( const double, const double, const double ) ;

       int operator== ( const Transformation&, const Transformation& ) ;
       int operator!= ( const Transformation&, const Transformation& ) ;

		// Output

       ostream& operator<< ( ostream&, const Transformation& ) ;

		// Arithmetic Operations

       Transformation operator+ ( const Transformation&, const Transformation& ) ;
       Transformation operator- ( const Transformation&, const Transformation& ) ;
       Transformation operator- ( const Transformation& ) ;
       Transformation operator* ( const double, const Transformation& ) ;
       Transformation operator* ( const Transformation&, const double ) ;
       Transformation operator* ( const Transformation&, const Transformation& ) ;
	Transformation frame_to_frame ( const Frame&, const Frame& ) ;
#endif

