#include "Boonas.h"
#include "Transformation.h"

Boonas::Boonas(int argc, char** argv)
{
	cursor = 0;
	orig = new LNHHolder();
	temp = 0;
	colorValue = 0;
	Transformation matrix;
	
	if(argc < 3)
	{
		return;
	}
	if(strcmp(argv[1], "polygon") == 0) // DONE
	{
		polygon(argc, argv); // default the color to a grey, or a blue
	}
	else if(strcmp(argv[1], "polygonC") == 0)
	{
		polygonC(argc, argv);
	}
	else if(strcmp(argv[1], "assemble") == 0) // DONE
	{
		assemble(argc, argv);
	}
	else if(strcmp(argv[1], "transform") == 0) //WORKS
	{
		loadFile(argv[2]); // loads the data into a LNHHolder 
		matrix = parseParams(3, argc, argv, matrix); 
		doMult(matrix); // applies the matrix transformation
		writeFile(argv[2]); // writes file;
	}
	else if(strcmp(argv[1], "create") == 0) // WORKS
	{
		loadFile(argv[3]);
		matrix = parseParams(4, argc, argv, matrix);
		doMult(matrix);
		writeFile(argv[2]);
	}
	else if(strcmp(argv[1], "extrude") == 0) // WORKS
	{
		loadFile(argv[2]);
		doExtrude(argv[4], argv[3]); // extrudes argv 3 distance
	}
	else if(strcmp(argv[1], "clip") == 0) // clip, file, inpolies, outpolies, normalx normaly normalz, pointx, pointy, pointz
	{
		loadFile(argv[2]);
		//doClip(argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
		doClip(argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
	}
	else if(strcmp(argv[1], "rot") == 0) // rot infile outfile vectorx, y, z pointx, y, z, divisions, degrees
	{
		loadFile(argv[2]);
		doRotate(argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
		writeFile(argv[3]);
	}
	return;
}

void Boonas::doRotate(QString outfile, QString vectx, QString vecty, QString vectz, QString px, QString py, QString pz, QString divisions, QString degrees) 
{
	Point centerP(px.toFloat(), py.toFloat(), pz.toFloat());
	Vector centerV(vectx.toFloat(), vecty.toFloat(), vectz.toFloat());
	Transformation matrix;
	float theta;
	float phi;
	float angleOfRot = degrees.toFloat() / divisions.toFloat();
	
	// translate to x
	matrix = xt(-px.toFloat(), matrix);
	matrix = yt(-py.toFloat(), matrix);
	matrix = zt(-pz.toFloat(), matrix);
	
	
	if(vectz.toFloat() == 0)
	{
		if((vectx.toFloat() == 1) && (vectz.toFloat() == 0))
		{
			theta = 1.57079633;
		}
		else
		{
			theta = 0.0;
		}
	}
	else
	{
		theta = atan(vectx.toFloat() / vectz.toFloat());
	}
	
	matrix = yr(-theta, matrix);
	phi = atan(vecty.toFloat() / (sqrt((vectx.toFloat() * vectx.toFloat()) + (vectz.toFloat() * vectz.toFloat()))));
	matrix = xr(phi, matrix);
	
	// apply matrix
	doMult(matrix);
	
	// do rotates and divisions along Z
	doZrm(outfile, angleOfRot, divisions.toFloat());
	
	// have to re-read from a temp file after this
	delete orig;
	orig = new LNHHolder();
	readTfile(outfile);
	
	//unrotate
	matrix = Transformation();
	matrix = xr(-phi, matrix);
	matrix = yr(theta, matrix);
	
	// untranslate
	matrix = xt(px.toFloat(), matrix);
	matrix = yt(py.toFloat(), matrix);
	matrix = zt(pz.toFloat(), matrix);
	
	// apply matrix
	doMult(matrix);
	
	return;
}

void Boonas::readTfile(QString filename) 
{
	float x, y, z, w;
	bool firstRun = true;
	QStringList coordList; // list of floats
	QString line;
	filename.append(".polyTemp");
	QFile* theSource;
	theSource = new QFile(filename);
	theSource -> open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream inStream( theSource );
	
	orig -> reset();
	
	while(!inStream.atEnd())
	{
		line = inStream.readLine();
		if(line.contains("newObject")) // if it does it is a new object
		{
			if(firstRun) // dont add a blank linknodeholder
			{
				firstRun = false;
				temp = new LinkNodeHolder();
			}
			else // add old completed one and make a new one
			{
				orig -> add(temp);
				temp = new LinkNodeHolder();
			}
		}
		else
		{
			coordList = line.split(" "); // splits line into list of 2 floats
			x = coordList.at(0).toFloat(); // convert both strings to floats
			y = coordList.at(1).toFloat();
			z = coordList.at(2).toFloat();
			w = 1.0;
			temp -> add(x, y, z, w); // add the floats to the system
		}
	}
	orig -> add(temp);
	orig -> reset();
	
	theSource -> close();
	theSource -> remove();
	delete theSource;
}

void Boonas::doZrm(QString outfile, float angleOfRot, float divisions) // angle of rot is in degrees 
{
	Transformation matrix;
	outfile.append(".polyTemp");
	float x, y, z, w;
	bool again = true;
	QFile* theOutDestination;
	theOutDestination = new QFile(outfile);
	theOutDestination -> remove();
	theOutDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theOutDestination );
	
	matrix = zd(angleOfRot, matrix);
	
	for(int i = 0; i < divisions; i++) // do it for the total number of divisions
	{
		again = true;
		orig -> reset();
		//write to file
		do // do this loop while ther is more in orig
		{
			
			cursor = orig -> getCurrent(); // cursor is current
			cursor -> reset();
			
			//change color respectively for each object
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			
			if(colorValue != 0)
			{
				delete colorValue;
				colorValue = 0;
			}
			colorValue = new Point(x, y, z);
			
			cursor -> advance();
			
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			
			if(!(orig -> isNotLast()))
			{
				again = false;
			}
			
			outStream << "newObject" << endl;
			
			// put out color vector
			outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
			
			do
			{
				x = cursor -> getX(); // get point
				y = cursor -> getY();
				z = cursor -> getZ();
				w = cursor -> getW();
				outStream << x << " " << y << " " << z << " " << w << endl;
				//qDebug() << "runing through before mult then after";
				//qDebug() << x << " " << y << " " << z << " " << w;
				cursor -> advance();
			}
			while(cursor -> hasNext()); // run through the points and mult!
			
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			outStream << x << " " << y << " " << z << " " << w << endl;
			
			
			cursor -> reset();
			
			orig -> advance(); // advance what were working with
		}
		while(again);
		
		//do rotate
		doMult(matrix);
	}
	
	return;
}

void Boonas::doClip(QString infile, QString normalx, QString normaly, QString normalz, QString px, QString py, QString pz)
{
	// set up to impliment an outfile but not needed yet
	// set up base variables
	Point planeP(px.toFloat(), py.toFloat(), pz.toFloat());
	QString outfile = "temporary";
	Vector planeN(normalx.toFloat(), normaly.toFloat(), normalz.toFloat());
	float x, y, z;
	Point* thisPoint = 0;
	Point* lastPoint = 0;
	Point* firstPoint = 0;
	
	float lastD = 0;
	float thisD = 0;
	float firstD = 0;
	bool firstObjectIn = false;
	bool firstObjectOut = false;
	bool firstTimeThisRun = true;
	
	// set up test bariables
	bool again = true;
	bool lastPointOut = false;
	bool thisPointOut = false;
	bool lastPointOn = false;
	bool thisPointOn = false;
	orig -> reset(); // orig is at start
	
	// set up file to write in poly's to
	infile.append(".poly");
	QFile* theInDestination;
	theInDestination = new QFile(infile);
	theInDestination -> remove();
	theInDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream inStream( theInDestination );
	
	// set up file to write out poly's to
	outfile.append(".poly");
	QFile* theOutDestination;
	theOutDestination = new QFile(outfile);
	theOutDestination -> remove();
	theOutDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theOutDestination );
	
	// run through the list
	do // do this loop while ther is more in orig, one more will be left after
	{
		cursor = orig -> getCurrent(); // cursor is current
		cursor -> reset();
		
		
		//change color respectively for each object
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		if(colorValue != 0)
		{
			delete colorValue;
			colorValue = 0;
		}
		colorValue = new Point(x, y, z);
		
		cursor -> advance();
		
		
		//inStream << "newObject" << endl;
		//outStream << "newObject" << endl;
		lastPoint = 0;
		thisPoint = 0;
		
		firstObjectIn = false;
		firstObjectOut = false;
		firstTimeThisRun = true;
		
		if(!(orig -> isNotLast()))
		{
			again = false;
		}
		do
		{
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			
			if(thisPoint != 0)// if curpoint is not null, make it so
			{
				delete thisPoint;
			}
			
			thisPoint = new Point(x, y, z);// create new point
			
			if(firstTimeThisRun)
			{
				firstTimeThisRun = false;
				firstPoint = new Point(x, y, z);
				firstD = dot((*thisPoint - planeP), planeN);
			}
			
			thisD = dot((*thisPoint - planeP), planeN);
			
			if(dot((*thisPoint - planeP), planeN) > 0)// in
			{
				thisPointOut = false;
				thisPointOn = false;
			}
			else if(dot((*thisPoint - planeP), planeN) < 0)// out
			{
				thisPointOut = true;
				thisPointOn = false;
			}
			else// on
			{
				thisPointOn = true;
			}
			
			if(lastPoint == 0) // if there is not a last point
			{
				lastPoint = new Point(thisPoint -> x(), thisPoint -> y(), thisPoint -> z());
				lastPointOut = thisPointOut;
				lastPointOn = thisPointOn;
				lastD = thisD;
			}
			else
			{
				// do test to see if last was out and this was in. and delete whats necisarry
				if(lastPointOn) // last point was on add it
				{
					if(firstObjectIn == false)
					{
						inStream << "newObject" << endl;
						inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectIn = true;
					}
					if(firstObjectOut == false)
					{
						outStream << "newObject" << endl;
						outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectOut = true;
					}
					outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
					inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				}
				else if(lastPointOut && thisPointOut) // only add to outstream
				{
					if(firstObjectOut == false)
					{
						outStream << "newObject" << endl;
						
						// put out color vector
						outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
						
						firstObjectOut = true;
					}
					outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				}
				else if((lastPointOut == false) && (thisPointOut == false)) // only add to instream
				{
					if(firstObjectIn == false)
					{
						inStream << "newObject" << endl;
						
						// put out color vector
						inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectIn = true;
					}
					inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				}
				else if((lastPointOut == false) && thisPointOut) // add last point to in, and the center to in and out
				{
					if(firstObjectIn == false)
					{
						inStream << "newObject" << endl;
						
						// put out color vector
						inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectIn = true;
					}
					if(firstObjectOut == false)
					{
						outStream << "newObject" << endl;
						
						// put out color vector
						outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectOut = true;
					}
					inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
					*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
					inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
					outStream << lastPoint -> x()<< " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;	
				}
				else // lastpoint out, this point in, add center to both, advance
				{
					if(firstObjectIn == false)
					{
						inStream << "newObject" << endl;
						
						// put out color vector
						inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectIn = true;
					}
					if(firstObjectOut == false)
					{
						outStream << "newObject" << endl;
						
						// put out color vector
						outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
						
						firstObjectOut = true;
					}
					*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
					inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
					outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				}
				
				// remove it
				delete lastPoint;
				
				// transfer this point to last, get ready to run again
				lastPoint = new Point(thisPoint -> x(), thisPoint -> y(), thisPoint -> z());
				lastPointOut = thisPointOut;
				lastPointOn = thisPointOn;
				lastD = thisD;
			}
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!
		
			
		// this is the last point in this object
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
			
		if(thisPoint != 0)
		{
			delete thisPoint;
		}
		
		thisPoint = new Point(x, y, z);// create new point
		
		thisD = dot((*thisPoint - planeP), planeN);
		
		if(dot((*thisPoint - planeP), planeN) > 0)// in
		{
			thisPointOut = false;
			thisPointOn = false;
		}
		else if(dot((*thisPoint - planeP), planeN) < 0)// out
		{
			thisPointOut = true;
			thisPointOn = false;
		}
		else// on
		{
			thisPointOn = true;
		}
		
		if(lastPoint != 0) // there was a last point
		{
			if(lastPointOn) // last point was on add it
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
			}
			else if(lastPointOut && thisPointOut) // only add to outstream
			{
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
			}
			else if((lastPointOut == false) && (thisPointOut == false)) // only add to instream
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
			}
			else if((lastPointOut == false) && thisPointOut) // add last point to in, and the center to in and out
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;	
			}
			else // lastpoint out, this point in, add center to both, advance
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
			}
			
			// remove it
			delete lastPoint;
		}
		
		
		thisD = dot((*thisPoint - planeP), planeN);
		
		// do the test for the last point!
		if(dot((*thisPoint - planeP), planeN) > 0)// in
		{
			if(firstObjectIn == false)
			{
				inStream << "newObject" << endl;
				
				// put out color vector
				inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
				
				firstObjectIn = true;
			}
			inStream << thisPoint -> x() << " " << thisPoint -> y() << " " << thisPoint -> z() << " " << 1 << endl;
		}
		else if(dot((*thisPoint - planeP), planeN) < 0)// out
		{
			if(firstObjectOut == false)
			{
				outStream << "newObject" << endl;
				
				// put out color vector
				outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
				
				firstObjectOut = true;
			}
			outStream << thisPoint -> x() << " " << thisPoint -> y() << " " << thisPoint -> z() << " " << 1 << endl;
		}
		else// on
		{
			if(firstObjectIn == false)
			{
				inStream << "newObject" << endl;
				
				// put out color vector
				inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
				
				firstObjectIn = true;
			}
			if(firstObjectOut == false)
			{
				outStream << "newObject" << endl;
				
				// put out color vector
				outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
				
				firstObjectOut = true;
			}
			inStream << thisPoint -> x() << " " << thisPoint -> y() << " " << thisPoint -> z() << " " << 1 << endl;
			outStream << thisPoint -> x() << " " << thisPoint -> y() << " " << thisPoint -> z() << " " << 1 << endl;
		}
		
		//special compare for case where first point was out, and last point was in, or first point was in and last is out, take care of looping
		if(firstPoint != 0)// if this isn't a one point set, should never happen, but speed isn't an issue and can't be too sure
		{
			// substitute values so code can be copied and pasted from above!
			lastPoint = thisPoint;
			lastD = thisD;
			thisPoint = firstPoint;
			thisD = firstD;
			// right now lastpoint is the last point, and this point is the first point of the set
			// we are ready to do a normal case
			
			// find out if the first point was in or out
			if(dot((*thisPoint - planeP), planeN) > 0)// in
			{
				thisPointOut = false;
				thisPointOn = false;
			}
			else if(dot((*thisPoint - planeP), planeN) < 0)// out
			{
				thisPointOut = true;
				thisPointOn = false;
			}
			else// on
			{
				thisPointOn = true;
			}
			
			//find out if the last point was in or out
			if(dot((*lastPoint - planeP), planeN) > 0)// in
			{
				lastPointOut = false;
				lastPointOn = false;
			}
			else if(dot((*lastPoint - planeP), planeN) < 0)// out
			{
				lastPointOut = true;
				lastPointOn = false;
			}
			else// on
			{
				lastPointOn = true;
			}
			
			//put midpoint out to files accordingly, remember, do NOT add last point twice!
			if((lastPointOut == false) && thisPointOut) // add the center to in and out
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;	
			}
			else if(lastPointOut && (thisPointOut == false)) // lastpoint out, this point in, add center to both, advance
			{
				if(firstObjectIn == false)
				{
					inStream << "newObject" << endl;
					
					// put out color vector
					inStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectIn = true;
				}
				if(firstObjectOut == false)
				{
					outStream << "newObject" << endl;
					
					// put out color vector
					outStream << colorValue -> x() << " " << colorValue -> y() << " " << colorValue -> z() << " 1" << endl;
					
					firstObjectOut = true;
				}
				*lastPoint = getCenter(lastPoint, thisPoint, lastD, thisD); //returns center
				inStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
				outStream << lastPoint -> x() << " " << lastPoint -> y() << " " << lastPoint -> z() << " " << 1 << endl;
			}
		}
		
		
		cursor -> reset();
		
		orig -> advance(); // advance what were working with
	}
	while(again);
	
	orig -> reset();
	
	theInDestination -> close();
	theOutDestination -> close();
	theOutDestination -> remove(); // remove it untill we use it, has a bug, but not needed so no need to fix
	
	return;
}

Point Boonas::getCenter(Point* pointA, Point* pointB, float dOne, float dTwo) 
{
	Point returnP;
	float t;
	t = (dOne / (dOne - dTwo));
	
	returnP = *pointA + (t * (*pointB - *pointA));
	return returnP;
}

Transformation Boonas:: parseParams(int start, int argc, char** argv, Transformation matrix) 
{
	QString currIn;
	
	for(int i = start; i < (argc - 1); i += 2) // iterate through parameters skiping every other
	{
		if(strcmp(argv[i], "XT") == 0)
		{
			currIn = argv[i + 1];
			matrix = xt(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "YT") == 0)
		{
			currIn = argv[i + 1];
			matrix = yt(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "ZT") == 0)
		{
			currIn = argv[i + 1];
			matrix = zt(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "XS") == 0)
		{
			currIn = argv[i + 1];
			matrix = xs(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "YS") == 0)
		{
			currIn = argv[i + 1];
			matrix = ys(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "ZS") == 0)
		{
			currIn = argv[i + 1];
			matrix = zs(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "US") == 0)
		{
			currIn = argv[i + 1];
			matrix = us(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "XD") == 0)
		{
			currIn = argv[i + 1];
			matrix = xd(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "YD") == 0)
		{
			currIn = argv[i + 1];
			matrix = yd(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "ZD") == 0)
		{
			currIn = argv[i + 1];
			matrix = zd(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "XR") == 0)
		{
			currIn = argv[i + 1];
			matrix = xr(currIn.toFloat(), matrix);
		}
		else if(strcmp(argv[i], "YR") == 0)
		{
			currIn = argv[i + 1];
			matrix = yr(currIn.toFloat(), matrix);
		}
		else // MUST BE ZR
		{
			currIn = argv[i + 1];
			matrix = zr(currIn.toFloat(), matrix);
		}
	}
	
	return matrix;
}

void Boonas::doMult(Transformation matrix)
{
	float x, y, z, w;
	ProjPoint* curPoint = 0;
	ProjPoint tempPoint;
	bool again = true;
	orig -> reset(); // orig is at start
	
	do // do this loop while ther is more in orig
	{
		
		cursor = orig -> getCurrent(); // cursor is current
		cursor -> reset();
		
		// skip color values
		cursor -> advance();
		
		if(!(orig -> isNotLast()))
		{
			again = false;
		}
		do
		{
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			if(curPoint != 0)
			{
				delete curPoint;
			}
			
			curPoint = new ProjPoint(x, y, z, w);
			tempPoint = matrix.applied_to(*curPoint);
			
			cursor -> setX(tempPoint.x());
			cursor -> setY(tempPoint.y());
			cursor -> setZ(tempPoint.z());
			cursor -> setW(tempPoint.w());
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!
		
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
			
		if(curPoint != 0)
		{
			delete curPoint;
		}
			
		curPoint = new ProjPoint(x, y, z, w);
		tempPoint = matrix.applied_to(*curPoint);
			
		cursor -> setX(tempPoint.x());
		cursor -> setY(tempPoint.y());
		cursor -> setZ(tempPoint.z());
		cursor -> setW(tempPoint.w());
		
		cursor -> reset();
		
		orig -> advance(); // advance what were working with
	}
	while(again);
	
	orig -> reset();
	
	return;
}

void Boonas::loadFile(QString filename)
{
	float x, y, z, w;
	bool firstRun = true;
	QStringList coordList; // list of floats
	QString line;
	filename.append(".poly");
	QFile* theSource;
	theSource = new QFile(filename);
	theSource -> open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream inStream( theSource );
	
	orig -> reset();
	
	while(!inStream.atEnd())
	{
		line = inStream.readLine();
		if(line.contains("newObject")) // if it does it is a new object
		{
			if(firstRun) // dont add a blank linknodeholder
			{
				firstRun = false;
				temp = new LinkNodeHolder();
			}
			else // add old completed one and make a new one
			{
				orig -> add(temp);
				temp = new LinkNodeHolder();
			}
		}
		else
		{
			coordList = line.split(" "); // splits line into list of 2 floats
			x = coordList.at(0).toFloat(); // convert both strings to floats
			y = coordList.at(1).toFloat();
			z = coordList.at(2).toFloat();
			w = 1.0;
			temp -> add(x, y, z, w); // add the floats to the system
		}
	}
	orig -> add(temp);
	orig -> reset();
	
	theSource -> close();
	delete theSource;
}

void Boonas::polygonC(int argc, char** argv)
{
	QString filename = argv[2];
	int point = 0; // count to have right format
	filename.append(".poly");
	QFile* theDestination;
	theDestination = new QFile(filename);
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theDestination );
	
	outStream << "newObject" << endl;
	
	//assume first 3 points are color 4f values!
	outStream << argv[3] << " " << argv[4] << " " << argv[5] << " 1" << endl;
	
	for(int i = 6; i < argc; i++)
	{
		if(point == 2) // have to add 3rd verticie and end line
		{
			outStream << "1 1" << endl;
			point = 0;
		}
		point++;
		outStream << argv[i] << " ";
	}
	outStream << "1 1" << endl;
	
	theDestination -> close();
	delete theDestination;
	
	return;
}

void Boonas::polygon(int argc, char** argv) 
{
	QString filename = argv[2];
	int point = 0; // count to have right format
	filename.append(".poly");
	QFile* theDestination;
	theDestination = new QFile(filename);
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theDestination );
	
	outStream << "newObject" << endl;
	
	//assume a default color, place it here
	outStream << "-1 " << "-1 " << "2 " << "1" << endl;
	
	for(int i = 3; i < argc; i++)
	{
		if(point == 2) // have to add 3rd verticie and end line
		{
			outStream << "1 1" << endl;
			point = 0;
		}
		point++;
		outStream << argv[i] << " ";
	}
	outStream << "1 1" << endl;
	
	theDestination -> close();
	delete theDestination;
}

void Boonas::assemble(int argc, char** argv) 
{
	QString inFileName;
	QString line;
	
	QString outFileName = argv[argc - 1];
	outFileName.append(".poly");
	
	QFile* theDestination;
	QFile* theSource;
	
	QTextStream* outStream;
	theDestination = new QFile(outFileName);
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream inStream( theDestination ); // sets up file to write out to
	
	for(int i = 2; i < (argc - 1); i++)// iterate through in files
	{
		
		inFileName = argv[i];
		inFileName.append(".poly");
		theSource = new QFile(inFileName);
		theSource -> open(QIODevice::ReadOnly | QIODevice::Text);
		outStream = new QTextStream( theSource );
		while( !outStream -> atEnd()) // iterate through lines
		{
			line = outStream -> readLine();
			inStream << line << endl;
		}
		delete outStream; // clean up nicely
		theSource -> close();
		delete theSource;
	}
	
	theDestination -> close(); // close niceley
	delete theDestination;
}

Transformation Boonas::xt(float x, Transformation matrix)
{
	return matrix * translate_by(x, 0, 0);
}

Transformation Boonas::yt(float x, Transformation matrix)
{
	return matrix * translate_by(0, x, 0);
}

Transformation Boonas::zt(float x, Transformation matrix)
{
	return matrix * translate_by(0, 0, x);
}

Transformation Boonas::xs(float x, Transformation matrix)
{
	return matrix * scale_by(x, 1, 1);
}

Transformation Boonas::ys(float x, Transformation matrix)
{
	return matrix * scale_by(1, x, 1);
}

Transformation Boonas::zs(float x, Transformation matrix)
{
	return matrix * scale_by(1, 1, x);
}

Transformation Boonas::us(float x, Transformation matrix)
{
	return matrix * scale_by(x, x, x);
}

Transformation Boonas::xd(float x, Transformation matrix)
{
	return matrix * x_rotate_by(x);
}

Transformation Boonas::yd(float x, Transformation matrix)
{
	return matrix * y_rotate_by(x);
}

Transformation Boonas::zd(float x, Transformation matrix)
{
	return matrix * z_rotate_by(x);
}

Transformation Boonas::xr(float x, Transformation matrix)
{
	x = x * (180.0/ 3.1415926535897);
	return matrix * x_rotate_by(x);
}

Transformation Boonas::yr(float x, Transformation matrix)
{
	x = x * (180.0/ 3.1415926535897);
	return matrix * y_rotate_by(x);
}

Transformation Boonas::zr(float x, Transformation matrix)
{
	x = x * (180.0/ 3.1415926535897);
	return matrix * z_rotate_by(x);
}

void Boonas::writeFile(QString filename)
{
	float x, y, z, w;
	bool again = true;
	filename.append(".poly");
	QFile* theDestination;
	theDestination = new QFile(filename);
	theDestination -> remove();
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theDestination );
	
	do // do this loop while ther is more in orig
	{
		
		cursor = orig -> getCurrent(); // cursor is current
		cursor -> reset();
		
		if(!(orig -> isNotLast()))
		{
			again = false;
		}
		
		outStream << "newObject" << endl;
		
		do
		{
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			outStream << x << " " << y << " " << z << " " << w << endl;
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points!
		
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		outStream << x << " " << y << " " << z << " " << w << endl;
		
		
		cursor -> reset();
		
		orig -> advance(); // advance what were working with
	}
	while(again);
	
	theDestination -> close();
	delete theDestination;
}

void Boonas::doExtrude(QString num, QString filename) // extrudes and writes whilst extruding 
{
	float n = num.toFloat();
	float x, y, z, w;
	int numSides;
	Point* pa;
	Point* pb;
	Point* pc;
	Point pd;
	Point firstPoint;
	Vector va;
	Vector vb;
	Vector vn;
	bool again = true;
	filename.append(".poly");
	QFile* theDestination;
	theDestination = new QFile(filename);
	theDestination -> remove();
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theDestination );
	
	do // do this loop while ther is more in orig
	{
		
		cursor = orig -> getCurrent(); // cursor is current
		cursor -> reset();
		
		//change color respectively for each object
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		if(colorValue != 0)
		{
			delete colorValue;
			colorValue = 0;
		}
		colorValue = new Point(x, y, z);
		
		cursor -> advance();
		
		if(!(orig -> isNotLast()))
		{
			again = false;
		}
		
		// get initial points in order to get unit vectior
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pa = new Point(x, y, z);
		
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pb = new Point(x, y, z);
		
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pc = new Point(x, y, z);
		
		va = *pa - *pb;
		vb = *pb - *pc;
		
		vn = cross(va, vb);
		vn.normalize();
		
		//vn = vn * -1.0; // flip it
		
		vn = vn * n;
		// vn is vector!
		
		cursor -> reset(); // reset cursor so 2nd iteration starts from begining
		
		
		// skip color vector
		cursor -> advance();
		
		numSides = 0;
		
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		// first iteration, copy orig polygon, count number of sides
		do
		{
			numSides++;
			//qDebug() << "Test results";
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			outStream << x << " " << y << " " << z << " " << w << endl;
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!k
		
		numSides++;
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		outStream << x << " " << y << " " << z << " " << w << endl;
		//numsides is the number of points
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		// second iteration, copy the top polygon
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		// second iteration, copy orig polygon to traversed points, count number of sides
		do
		{
			//qDebug() << "Test results";
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl;
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!k
		
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		delete pa;
		pa = new Point(x, y, z);
		
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl;
		// start next run time for the sides yo
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		
		for(int i = 0; i < (numSides - 1); i++) // run through this next bit for each side of the polygon except the last side
		{
			cursor -> reset();
			
			// skip color vector
			cursor -> advance();
			
			outStream << "newObject" << endl;
			
			// put out color vector
			outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
			
			for(int j = 0; j < i; j++) // advance cursor to get it to desired point
			{
				cursor -> advance();
			}
			
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			outStream << x << " " << y << " " << z << " " << w << endl; // out put orig point
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point a
			
			cursor -> advance(); //advance to next point;
			
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point b

			outStream << x << " " << y << " " << z << " " << w << endl; // out put last point
		}
		// now we only have to deal with the last side
		
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		for(int i = 0; i < numSides; i++)
		{
			cursor -> advance(); // advance cursor to last point;
		}
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		outStream << x << " " << y << " " << z << " " << w << endl; // out put first point
		
		delete pa;
		pa = new Point(x, y, z);
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point a
		
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		delete pa;
		pa = new Point(x, y, z);
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point b
		
		outStream << x << " " << y << " " << z << " " << w << endl; // out put last point
		
		orig -> advance(); // advance what were working with
	}
	while(again);
	
	theDestination -> close();
	delete theDestination;
	delete pa;
	delete pb;
	delete pc;
}