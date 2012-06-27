//
// ============================================================
//
//	      Transformation Implementation
//
// ============================================================
//
//
//
//      Copyright (C) 1997
//
//		      Professor Kenneth I. Joy
//		      Computer Science Department
//		      University of California
//		      Davis, CA  95616
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
#include "Transformation.h"

#define		TRUE		1
#define		FALSE		0

const double	 pi = 3.1415926535897 ;
using namespace std;
/*
   ============================================================

		CONSTRUCTOR

   ============================================================
*/

Transformation :: Transformation ()

   {
      id() ;
   }

/*
   ============================================================

		COPY CONSTRUCTOR

   ============================================================
*/

Transformation :: Transformation ( const Transformation& t )

   {
      for ( int i = 0 ; i < 4 ; i++ )
	 for ( int j = 0 ; j < 4 ; j++ )
	    _matrix[i][j] = t._matrix[i][j] ;
   }

/*
   ============================================================

		DESTRUCTOR

   ============================================================
*/

Transformation :: ~Transformation ()  { }

/*
   ============================================================

		ASSIGNMENT

   ============================================================
*/

Transformation& Transformation :: operator= ( const Transformation& t )

   {
      if ( this == &t ) return ( *this ) ;

      for ( int i = 0 ; i < 4 ; i++ )
	 for ( int j = 0 ; j < 4 ; j++ )
	    _matrix[i][j] = t._matrix[i][j] ;
      
      return ( *this ) ;
   }

/*
   ============================================================

		COMPARISONS

   ============================================================
*/

int  operator== ( const Transformation& t1, const Transformation& t2 ) 

   {
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ ) {
	 for ( j = 0 ; j < 4 ; j++ ) {
	    if ( t1._matrix[i][j] != t2._matrix[i][j] ) return ( FALSE ) ;
	    }
	 }

      return ( TRUE ) ;
   }

int  operator!= ( const Transformation& t1, const Transformation& t2 ) 

   {
      return ( ! ( t1 == t2 ) ) ;
   }


/*
   ============================================================

		OUTPUT

   ============================================================
*/

ostream& operator<< ( ostream& co, const Transformation& t ) 

   {
      for ( int i = 0 ; i < 4 ; i++ ) {
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    co << "\t" << t._matrix[i][j] ;
	    }
	 co << endl ;
	 }

      return ( co ) ;
   }

/*
   ============================================================

		MATRIX

   ============================================================
*/

double Transformation :: matrix ( const int i, const int j ) const

   {
      if ( ( i < 0 ) || ( i > 3 ) ||
	   ( j < 0 ) || ( j > 3 ) ) {
	 cerr << "Illegal subscripts ("
	      << i << ", " << j << ") to operator() in the "
	      << "Transformation class" << endl ;
	 exit ( 200 ) ;
	 }
      
      return ( _matrix[i][j] ) ;
   }

/*
   ============================================================

		ARITHMETIC FUNCTIONS

   ============================================================
*/

Transformation  operator+ ( const Transformation& t1, 
			      const Transformation& t2 ) 

   {
      Transformation		tt ;
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    tt._matrix[i][j] = t1._matrix[i][j] + t2._matrix[i][j] ;

      return ( tt ) ;
   }

Transformation  operator- ( const Transformation& t1, 
			      const Transformation& t2 ) 

   {
      Transformation		tt ;
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    tt._matrix[i][j] = t1._matrix[i][j] - t2._matrix[i][j] ;

      return ( tt ) ;
   }

Transformation  operator- ( const Transformation& t )

   {
      Transformation		tt ;
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    tt._matrix[i][j] = -t._matrix[i][j] ;

      return ( tt ) ;
   }

Transformation  operator* ( const double c, const Transformation& t ) 

   {
      Transformation		tt ;
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    tt._matrix[i][j] = c * t._matrix[i][j] ;

      return ( tt ) ;
   }

Transformation  operator* ( const Transformation& t, const double c ) 

   {
      Transformation		tt ;
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    tt._matrix[i][j] = c * t._matrix[i][j] ;

      return ( tt ) ;
   }


Transformation  operator* ( const Transformation& t1, 
			      const Transformation& t2 ) 

   {
      Transformation		tt ;
      int 			i, j, k ;
      double			sum ;

      for ( i = 0 ; i < 4 ; i++ ) {
	 for ( j = 0 ; j < 4 ; j++ ) {

	    sum = 0.0 ;
	    for ( k = 0 ; k < 4 ; k++ ) {
	       sum += t1._matrix[i][k] * t2._matrix[k][j] ;
	       }

	    tt._matrix[i][j] = sum ;

	    }
	 }

      return ( tt ) ;
   }

Transformation  Transformation :: operator+= ( const Transformation& t ) 

   {
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    _matrix[i][j] += t._matrix[i][j] ;

      return ( *this ) ;
   }

Transformation  Transformation :: operator-= ( const Transformation& t ) 

   {
      int 		i, j ;

      for ( i = 0 ; i < 4 ; i++ )
	 for ( j = 0 ; j < 4 ; j++ )
	    _matrix[i][j] -= t._matrix[i][j] ;

      return ( *this ) ;
   }

Transformation  Transformation :: operator*= ( const Transformation& t )

   {
      double		tt[4][4] ;
      int 		i, j, k ;
      double		sum ;

      for ( i = 0 ; i < 4 ; i++ ) {
	 for ( j = 0 ; j < 4 ; j++ ) {

	    sum = 0.0 ;
	    for ( k = 0 ; k < 4 ; k++ ) {
	       sum += _matrix[i][k] * t._matrix[k][j] ;
	       }

	    tt[i][j] = sum ;

	    }
	 }

      for ( i = 0 ; i < 4 ; i++ ) 
	 for ( j = 0 ; j < 4 ; j++ ) 
	    _matrix[i][j] = tt[i][j] ;

      return ( *this ) ;
   }

/*
   ============================================================

		IDENTITY 

   ============================================================
*/

Transformation identity ()

   {
//    cout << "identity ()" << endl ; 

      Transformation t ;
      return ( t ) ;
   }

/*
   ============================================================

		TRANSLATE_BY 

   ============================================================
*/

Transformation translate_by (  const double x, 
				 const double y, 
				 const double z ) 

   {
//    cout << "translate_by ( "
//         << x << "," << y << "," << z << " )" << endl ;

      return ( translate_by ( Vector ( x, y, z ) ) ) ;
   }

Transformation translate_by ( const Vector v )

   {
//    cout << "translate_by ( "
//         << v << " )" << endl ;

      Transformation t ;
      t._matrix[3][0] = v.x() ;
      t._matrix[3][1] = v.y() ;
      t._matrix[3][2] = v.z() ;

      return ( t ) ;
   }

/*
   ============================================================

		SCALE_BY

   ============================================================
*/

Transformation scale_by (  const double x, 
			     const double y, 
			     const double z ) 

   {
//    cout << "scale_by ( "
//         << x << "," << y << "," << z << " )" << endl ;

      return ( scale_by ( Vector ( x, y, z ) ) ) ;
   }

Transformation scale_by ( const Vector v )

   {
//    cout << "scale_by ( "
//         << v << " )" << endl ;

      Transformation t ;
      t._matrix[0][0] = v.x() ;
      t._matrix[1][1] = v.y() ;
      t._matrix[2][2] = v.z() ;

      return ( t ) ;
   }

/*
   ============================================================

		X_ROTATE_BY

   ============================================================
*/

Transformation x_rotate_by ( const double parameter ) 

   {
		//  Note : parameter to this routine is considered
		//           to be in degrees, not radians

      Transformation tt ;

      double cp = cos ( parameter * pi / 180.0 ) ;
      double sp = sin ( parameter * pi / 180.0 ) ;

      tt._matrix[1][1] = cp ;
      tt._matrix[1][2] = sp ;
      tt._matrix[2][1] = -sp ;
      tt._matrix[2][2] = cp ;

      return ( tt ) ;
   }

/*
   ============================================================

		Y_ROTATE_BY

   ============================================================
*/

Transformation y_rotate_by ( const double parameter )

   {
		//  Note : parameter to this routine is considered
		//           to be in degrees, not radians

      Transformation tt ;

      double cp = cos ( parameter * pi / 180.0 ) ;
      double sp = sin ( parameter * pi / 180.0 ) ;

      tt._matrix[0][0] = cp ;
      tt._matrix[0][2] = -sp ;
      tt._matrix[2][0] = sp ;
      tt._matrix[2][2] = cp ;

      return ( tt ) ;
   }

/*
   ============================================================

		Z_ROTATE_BY

   ============================================================
*/

Transformation z_rotate_by ( const double parameter ) 

   {
		//  Note : parameter to this routine is considered
		//           to be in degrees, not radians

      Transformation tt ;

      double cp = cos ( parameter * pi / 180.0 ) ;
      double sp = sin ( parameter * pi / 180.0 ) ;

      tt._matrix[0][0] = cp ;
      tt._matrix[0][1] = sp ;
      tt._matrix[1][0] = -sp ;
      tt._matrix[1][1] = cp ;

      return ( tt ) ;
   }

/*
   ============================================================

		ROTATE_BY

   ============================================================
*/

Transformation rotate_by ( const double parameter,
			     const Vector& axis ) 

   {
		//  Note : parameter to this routine is considered
		//           to be in degrees, not radians

//    cout << "rotate_by ( "
//         << parameter << ", " << axis << " )" << endl ;

      double length1 = sqrt ( axis.x() * axis.x() + axis.z() * axis.z() ) ;
      double theta = atan2 ( axis.x(), axis.z() ) * 180.0 / pi ;
      double phi = atan2 ( axis.y(), length1 ) * 180.0 / pi ;

      return ( y_rotate_by ( -theta ) 
	     * x_rotate_by ( phi ) 
	     * z_rotate_by ( parameter ) 
	     * x_rotate_by ( -phi ) 
	     * y_rotate_by ( theta ) ) ;
   }

/*
   ============================================================

		ID

   ============================================================
*/

void Transformation :: id ()

   {
      for ( int i = 0 ; i < 4 ; i++ ) {
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    _matrix[i][j] = 0.0 ;
	    }
	 _matrix[i][i] = 1.0 ;
	 }

      return ;
   }

/*
   ============================================================

		VIEW

   ============================================================
*/

Transformation view ( const double near, 
		      const double far, 
		      const double angle )

   {
//    cout << "view ( "
//         << near << "," 
//         << far << "," 
//         << angle << " )" << endl ;

      if ( ( angle > 0.0 ) && ( near < far ) ) {
	 double tan_angle = tan ( angle * 0.5 * pi / 180.0 ) ;
	 double cot_angle = 1.0 / tan_angle ;

	 Transformation tt ;
	 tt._matrix[0][0] = cot_angle ;
	 tt._matrix[1][1] = cot_angle ;
	 tt._matrix[2][2] = ( far + near ) / ( far - near ) ;
	 tt._matrix[3][2] = 2.0 * near * far / ( far - near ) ;
	 tt._matrix[2][3] = -1.0 ;
	 tt._matrix[3][3] = 0.0 ;
	 cout << "Viewing Transform" << endl << tt ;
	 return ( tt ) ;
	 }

      return ( identity() ) ;
   }

/*
   ============================================================

		INVERSE_VIEW

   ============================================================
*/

Transformation inverse_view ( const double near, 
			      const double far, 
			      const double angle )

   {
//    cout << "inverse_view ( "
//         << near << "," 
//         << far << "," 
//         << angle << " )" << endl ;

      if ( ( angle > 0.0 ) && ( near < far ) ) {
	 double tan_angle = tan ( angle * 0.5 * pi / 180.0 ) ;

	 Transformation tt ;
	 tt._matrix[0][0] = tan_angle ;
	 tt._matrix[1][1] = tan_angle ;
	 tt._matrix[2][2] = 0.0 ;
	 tt._matrix[3][2] = -1.0 ;
	 tt._matrix[2][3] = ( far - near ) / ( 2.0 * near * far) ;
	 tt._matrix[3][3] = ( far + near ) / ( 2.0 * near * far) ;

	 return ( tt ) ;
	 }

      return ( identity() ) ;
   }

/*
   ============================================================

		APPLIED_TO VECTORS

   ============================================================
*/

Vector Transformation :: applied_to ( const Vector& v ) const

   {
      double	    sum, a[4], aa[4] ;

      a[0] = v.x() ;
      a[1] = v.y() ;
      a[2] = v.z() ;
      a[3] = 0.0 ;

      for ( int i = 0 ; i < 4 ; i++ ) {
	 sum = 0.0 ;
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    sum += a[j] * _matrix[j][i] ;
	    }
	 aa[i] = sum ;
	 }

      return ( Vector ( aa[0], aa[1], aa[2] ) ) ;
   }



/*
   ============================================================

		APPLIED_TO LISTOFVECTORS

   ============================================================
*/

ListOfVectors Transformation :: applied_to ( const ListOfVectors& v ) const

   {
      ListOfVectors l ;
      int n = v.length() ;

      for ( int i = 0 ; i < n ; i++ )
	 l.add ( applied_to ( v[i] ) ) ;

      return ( l ) ;
   }



/*
   ============================================================

		APPLIED_TO POINT

   ============================================================
*/

Point Transformation :: applied_to ( const Point& p ) const

   {
      double	    sum, a[4], aa[4] ;

      a[0] = p.x() ;
      a[1] = p.y() ;
      a[2] = p.z() ;
      a[3] = 1.0 ;

      for ( int i = 0 ; i < 4 ; i++ ) {
	 sum = 0.0 ;
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    sum += a[j] * _matrix[j][i] ;
	    }
	 aa[i] = sum ;
	 }

      if ( aa[3] != 1.0 ) {
	 aa[0] /= aa[3] ;
	 aa[1] /= aa[3] ;
	 aa[2] /= aa[3] ;
	 }

      return ( Point ( aa[0], aa[1], aa[2] ) ) ;
   }



/*
   ============================================================

		APPLIED_TO LISTOFPOINTS

   ============================================================
*/

ListOfPoints Transformation :: applied_to ( const ListOfPoints& p ) const

   {
      ListOfPoints l ;
      int n = p.length() ;

      for ( int i = 0 ; i < n ; i++ )
	 l.add ( applied_to ( p[i] ) ) ;

      return ( l ) ;
   }

/*
   ============================================================

		APPLIED_TO PROJPOINT

   ============================================================
*/

ProjPoint Transformation :: applied_to ( const ProjPoint& p ) const

   {
      double	    sum, a[4], aa[4] ;

      a[0] = p.x() ;
      a[1] = p.y() ;
      a[2] = p.z() ;
      a[3] = p.w() ;

      for ( int i = 0 ; i < 4 ; i++ ) {
	 sum = 0.0 ;
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    sum += a[j] * _matrix[j][i] ;
	    }
	 aa[i] = sum ;
	 }

      return ( ProjPoint ( aa[0], aa[1], aa[2], aa[3] ) ) ;
   }


/*
   ============================================================

		APPLIED_TO LISTOFPROJPOINTS

   ============================================================
*/


ListOfProjPoints Transformation :: applied_to 
			( const ListOfProjPoints& p ) const

   {
      ListOfProjPoints l ;
      int n = p.length() ;

      for ( int i = 0 ; i < n ; i++ )
	 l.add ( applied_to ( p[i] ) ) ;

      return ( l ) ;
   }

