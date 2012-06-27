#ifndef __Viewer_h__
#define __Viewer_h__

#include <QGLWidget>
#include <math.h>
#include <QSlider>
#include <QHBoxLayout>
#include <QFile>
#include "LNHHolder.h"
#include <QTextStream>
#include <QDebug>
#include <math.h>
#include <QDir>
#include <QTimer>
#include "Transformation.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QImage>
#include <iostream>



class Viewer : public QGLWidget
{
    Q_OBJECT

  public:
    Viewer(int argc, char** argv);
    QSize minimumSizeHint() const; // min size of widget
    QSize sizeHint() const; // start size ideal of widget

  private slots:
    void move();

  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void plotPicture(); // applies camera transform
    void readFile(QString filename); // reads in the contents of MightyMax.boone
    Frame getFrame(Point camera, Point focus); // creats destination frame out of the camera and focus point
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void updateVectors();
    void doYlook(float rotationAmount);
    void doXlook(float rotationAmount);
    Point doRotate(Vector rotV, Point pToRot, float degrees);
    LNHHolder* orig; // LNHHolder of the original points
    LNHHolder* current; // LNHHolder of the recursivly produced points
    LinkNodeHolder* textureID;
    LinkNodeHolder* cursor; // LinkNodeHolder* for work
    LinkNodeHolder* temp; // LinkNodeHolder* for work
    Point camera;
    Point focus;
    QPoint lastPos;
    QTimer *timer;
    int zinc;
    GLuint currentRID[1];
    Vector lookVector;
    Vector upVector;
    Vector sideVector;
};

#endif