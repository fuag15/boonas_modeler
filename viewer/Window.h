#ifndef __Window_h__
#define __Window_h__

#include <QGLWidget>
#include <math.h>
#include <QSlider>
#include <QHBoxLayout>

class Window : public QWidget // widget to hold other widgets
{
    Q_OBJECT
    
  public:
    
    Window(int argc, char** argv);

};

#endif
