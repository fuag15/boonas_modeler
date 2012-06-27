#ifndef __Boonas_h__
#define __Boonas_h__
#include "LNHHolder.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QStringList>
#include "Transformation.h"
#include "ProjPoint.h"
#include "Vector.h"
#include "QDebug"
#include <math.h>

class Boonas
{
	public:
		Boonas(int argc, char** argv);
		void readFile();
		LNHHolder* orig; // LNHHolder of the points
		LinkNodeHolder* cursor; // LinkNodeHolder* for work
		LinkNodeHolder* temp;
		Point* colorValue;
		void polygon(int argc, char** argv);
		void polygonC(int argc, char** argv);
		void assemble(int argc, char** argv);
		void loadFile(QString filename);
		void doMult(Transformation matrix);
		Transformation parseParams(int start, int argc, char** argv, Transformation matrix);
		void writeFile(QString filename);
		void doExtrude(QString num, QString filename);
		Transformation xt(float x, Transformation matrix);
		Transformation yt(float x, Transformation matrix);
		Transformation zt(float x, Transformation matrix);
		Transformation xs(float x, Transformation matrix);
		Transformation ys(float x, Transformation matrix);
		Transformation zs(float x, Transformation matrix);
		Transformation us(float x, Transformation matrix);
		Transformation xd(float x, Transformation matrix);
		Transformation yd(float x, Transformation matrix);
		Transformation zd(float x, Transformation matrix);
		Transformation xr(float x, Transformation matrix);
		Transformation yr(float x, Transformation matrix);
		Transformation zr(float x, Transformation matrix);
		void doClip(QString infile, QString normalx, QString normaly, QString normalz, QString px, QString py, QString pz);
		Point getCenter(Point* pointA, Point* pointB, float dOne, float dTwo);
		void doRotate(QString outfile, QString vectx, QString vecty, QString vectz, QString px, QString py, QString pz, QString divisions, QString degrees);
		void doZrm(QString outfile, float angleOfRot, float divisions);
		void readTfile(QString filename);
};


#endif