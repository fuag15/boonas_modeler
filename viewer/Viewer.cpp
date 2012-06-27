#include "Viewer.h"
#include "Window.h"

// USAGE: start x, start y, start z, you will focus along the positive z 20 units away from this

Viewer::Viewer(int argc, char** argv) : QGLWidget()
{
	zinc = 0;
	argc = 1; // get rid of focus
	grabKeyboard();
	orig = new LNHHolder();
	lookVector = Vector(.001, .001, 1);
	upVector = Vector(.001, 1, .001);
	sideVector = Vector(-1, .001, .001);
	cursor = 0;
	readFile(argv[1]);
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(33);
	//timer -> setInterval(zinc);

	QString argOne, argTwo, argThree;

	argOne = argv[2];
	argTwo = argv[3];
	argThree = argv[4];
	camera = Point(argOne.toFloat(), argTwo.toFloat(), argThree.toFloat());
	
	focus = Point(camera.x(), camera.y(), camera.z());
	
	for(int i = 0; i < 20; i++)
	{
		focus = focus + lookVector;
	}
	resize(400, 400);
}

Point Viewer::doRotate(Vector rotV, Point pToRot, float degrees) 
{
	Transformation matrix;
	float theta;
	float phi;
	//qDebug() << "attempting to rotate around an axis";
	//qDebug() << rotV.x() << rotV.y() << rotV.z();
	//qDebug() << "a point";
	//qDebug() << pToRot.x() << pToRot.y() << pToRot.z();
	
	if(rotV.x() == 0)
	{
		rotV = Vector(.001, rotV.y(), rotV.z());
	}
	if(rotV.y() == 0)
	{
		rotV = Vector(rotV.x(), .001, rotV.z());
	}
	if(rotV.z() == 0)
	{
		rotV = Vector(rotV.x(), rotV.y(), .001);
	}
	
	if(rotV.z() == 0)
	{
		//qDebug() << "got close to here";
		if((rotV.x() == 1) && (rotV.z() == 0))
		{
			theta = 1.57079633;
			//qDebug() << "got here";
			
		}
		else
		{
			theta = 0.0;
		}
	}
	else
	{
		theta = atan(rotV.x() / rotV.z());
		theta = theta * (180.0/ 3.1415926535897);
	}
	phi = atan(rotV.y() / (sqrt((rotV.x() * rotV.x()) + (rotV.z() * rotV.z()))));
	
	
	phi = phi * (180.0/ 3.1415926535897);
	//qDebug() << "theta is" << theta;
	matrix *= y_rotate_by(-theta);
	
	pToRot = matrix.applied_to(pToRot);
	matrix = Transformation();
	//qDebug() << "a point";
	//qDebug() << pToRot.x() << pToRot.y() << pToRot.z();
	
	matrix *= x_rotate_by(phi);
	
	// apply matrix
	pToRot = matrix.applied_to(pToRot);
	
	matrix = Transformation();
	// do rotates and divisions along Z
	//degrees = degrees * (180.0/ 3.1415926535897);
	matrix *= z_rotate_by(degrees);
	pToRot = matrix.applied_to(pToRot);
	
	//unrotate
	matrix = Transformation();
	matrix *= x_rotate_by(-phi);
	matrix *= y_rotate_by(theta);
	
	// apply matrix
	pToRot = matrix.applied_to(pToRot);
	
	return pToRot;
}

void Viewer::doYlook(float rotationAmount)
{
	Vector oldVector = lookVector;
	
	// rotate lookVector and upVector around sideVector
	focus = Point(0,0,0);
	focus += lookVector;
	// focus now needs to be rotated about
	focus = doRotate(sideVector, focus, rotationAmount);
	lookVector = focus - Point(0,0,0);
	lookVector.normalize();
	
	//if they were bad and tried to look up!
	if(((oldVector.z() <= 0) && (lookVector.z() >= 0)) || ((oldVector.z() >= 0) && (lookVector.z() <= 0)))
	{
		lookVector = oldVector;
	}
	
	//focus = Point(0,0,0);
	//focus += upVector;
	// focus now needs to be rotated about
	//focus = doRotate(sideVector, focus, rotationAmount);
	//upVector = focus - Point(0,0,0);
	//upVector.normalize();
	
	updateVectors();
}

void Viewer::doXlook(float rotationAmount)
{
	// rotate lookVector and sideVector around upVector
	
	focus = Point(0,0,0);
	focus += lookVector;
	// focus now needs to be rotated about
	focus = doRotate(upVector, focus, rotationAmount);
	lookVector = focus - Point(0,0,0);
	lookVector.normalize();
	
	
	focus = Point(0,0,0);
	focus += sideVector;
	// focus now needs to be rotated about
	focus = doRotate(upVector, focus, rotationAmount);
	sideVector = focus - Point(0,0,0);
	sideVector.normalize();
	
	updateVectors();
}

void Viewer::move()
{
	if(zinc > 0)
	{
		for(int i = 0; i < zinc; i++)
		{
			camera += lookVector;
		}
	}
	else if(zinc < 0)
	{
		for(int i = 0; i > zinc; i--)
		{
			camera -= lookVector;
		}
	}

	updateVectors();
	updateGL();
	//qDebug() << zinc;
}

void Viewer::updateVectors()
{
	focus = camera;
	
	if(lookVector.x() == 0)
	{
		lookVector = Vector(.001, lookVector.y(), lookVector.z());
	}
	if(lookVector.y() == 0)
	{
		lookVector = Vector(lookVector.x(), .001, lookVector.z());
	}
	if(lookVector.z() == 0)
	{
		lookVector = Vector(lookVector.x(), lookVector.y(), .001);
	}
	
	if(sideVector.x() == 0)
	{
		sideVector = Vector(.001, sideVector.y(), sideVector.z());
	}
	if(sideVector.y() == 0)
	{
		sideVector = Vector(sideVector.x(), .001, sideVector.z());
	}
	if(sideVector.z() == 0)
	{
		sideVector = Vector(sideVector.x(), sideVector.y(), .001);
	}
	
	if(upVector.x() == 0)
	{
		upVector = Vector(.001, upVector.y(), upVector.z());
	}
	if(upVector.y() == 0)
	{
		upVector = Vector(upVector.x(), .001, upVector.z());
	}
	if(upVector.z() == 0)
	{
		upVector = Vector(upVector.x(), upVector.y(), .001);
	}
	
	for(int i = 0; i < 20; i++)
	{
		focus = focus + lookVector;
	}
}

void Viewer::mousePressEvent(QMouseEvent *event)
{
	setMouseTracking(TRUE);
	grabMouse();
	lastPos = event -> pos();
	if (event->button() == Qt::LeftButton) 
	{
		zinc += 1;
		if(zinc > 5)
		{
			zinc = 10;
		}
	}
	else if (event -> button() == Qt::RightButton)
	{
		zinc -= 1;
		if(zinc < -5)
		{
			zinc = -10;
		}
	}
	else if (event -> button() == Qt::MidButton)
	{
		zinc = 0;
		setMouseTracking(FALSE);
		releaseMouse();
	}
	//timer -> setInterval(zinc);
}

void Viewer::keyPressEvent(QKeyEvent *event)
{
	event = 0;
	zinc = 0;
	releaseMouse();
	//releaseKeyboard();
	setMouseTracking(FALSE);
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
	Transformation matrix;
	float xchange, ychange;
	//xchange = event -> x() - lastPos.x();
	xchange = lastPos.x() - event -> x();
	ychange = lastPos.y() - event -> y();
	
	lastPos.setX(event -> x());
	lastPos.setY(event -> y());
	
	
	doXlook(xchange);
	if(lookVector.x() >= 0)
	{
		doYlook(ychange);
	}
	else
	{
		doYlook(-ychange);
	}
	
	// if looking left or right, use zrotate by
	//matrix *= y_rotate_by(xchange);
	
	//if looking up or down use xrotate by
	//if(((lookVector.x() <= -0.9) || (lookVector.x() >= 0.9))) //&& ((lookVector.y() <= 0.3) || (lookVector.y() >= -0.1)))
	//{
	//	matrix *= z_rotate_by(ychange);
	//}
	//else
	//{
	//	matrix *= x_rotate_by(-ychange);
	//}
	
	//focus = Point(0,0,0);
	//focus += lookVector;
	
	//focus = matrix.applied_to(focus);
	
	//lookVector = focus - Point(0,0,0);
	
	//lookVector.normalize();
	
	//updateVectors();
	
	//focus = camera;
	//
	//for(int i = 0; i < 20; i++)
	//{
	//	focus = focus + lookVector;
	//}
	updateGL();
}

void Viewer::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	GLfloat amb0[ ] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diff0[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat spec0[ ] = { 1.0, 1.0, 1.0, 1.0};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
	
	GLfloat mspec[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat memmis[ ] = {0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, memmis);
	
	glEnable(GL_LIGHT0);
	
	GLfloat position[ ] = {1, 1, 0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	return;
}

void Viewer::resizeGL(int w, int h) // sets gl up
{
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-100, 100, -100, 100, 1, 100);
    
    return;
}

void Viewer::paintGL() // paints gl
{
	//glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glOrtho(-100, 100, -100, 100, 0, 100);
	gluPerspective(90, 1, 1, 300);
	gluLookAt(camera.x(), camera.y(), camera.z(), focus.x(), focus.y(), focus.z(), upVector.x(), upVector.y(), upVector.z());
	plotPicture();
	return;
}

QSize Viewer::minimumSizeHint() const
{
     return QSize(50, 50);
}

QSize Viewer::sizeHint() const
{
     return QSize(400, 400);
}

void Viewer::plotPicture()// plots the picture
{
	float x;
	float y;
	float z;
	float w;
	bool again = true;
    
	orig -> reset();
	
	do
	{
	    glBegin(GL_POLYGON);
	    if(!(orig -> isNotLast()))
	    {
		again = false;
	    }
	    
	    cursor = orig -> getCurrent();
	    cursor -> reset();
	    
	    x = cursor -> getX();
	    y = cursor -> getY();
	    z = cursor -> getZ();
	    w = cursor -> getW();
	    
	    glColor3f(x, y, z);
	    
	    cursor -> advance();
	    
	    while(cursor -> hasNext())
	    {
		x = cursor -> getX();
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		glVertex3f(x, y, z);
		cursor -> advance();
	    }
	    
	    x = cursor -> getX();
	    y = cursor -> getY();
	    z = cursor -> getZ();
	    
	    glVertex3f(x, y, z);
	    
	    orig -> advance();
	    glEnd();
	}
	while(again);

	return;
}

void Viewer::readFile(QString filename) // reads a file
{
    float x, y, z, w; // 2 points
    QString line; //current line and file name
    QDir dir; // QDir to access current directory
    QFileInfo fileInfo; // stores info on each file
    QStringList coordList; // list of floats
    bool firstRun; // if its first run dont add temp
    QFile* theSource;// file pointer so i can handle X number of files
    
    theSource = 0; // set file pointer to null
    
    orig -> reset();
    
    dir.setFilter(QDir::Files);// sets a filter so it only gives me file names
    QFileInfoList list = dir.entryInfoList(); // contains list of all files in document
	
	firstRun = true; // dont add a blank member
	theSource = new QFile(filename);
	
	theSource -> open(QIODevice::ReadOnly | QIODevice::Text);// opens file
	
	QTextStream stream( theSource ); // Set the stream to read
	while( !stream.atEnd())// while theres more file
	{
		line = stream.readLine();// read a line
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
			//qDebug() << x << " " << y << " " << z << " " << w;
			temp -> add(x, y, z, w); // add the floats to the system
		}
	}
	
	delete theSource; //frees up space that won't be used again;
	orig -> add(temp); // add the last one assumes a non black file
    
    orig -> reset(); // reset the orig queue

    return;
}
