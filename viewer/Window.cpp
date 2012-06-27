#include "Window.h"
#include "Viewer.h"

Window::Window(int argc, char** argv):QWidget()
{
    //QSlider *slider = new QSlider(Qt::Vertical);
    //slider->setRange(0, 10);
    //slider->setValue(3);
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(1000);
    
    Viewer *viewer = new Viewer(argc, argv);
    
    //connect(slider, SIGNAL(valueChanged(int)), viewer, SLOT(setIter(int)));
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(viewer);
    //layout->addWidget(slider);
    setLayout(layout);
    
}
