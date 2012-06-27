#include <QApplication>
//#include "Viewer.h"
//#include "Window.h"
#include "Window.h"

int main(int argc, char **argv)
{
	//Boonas prog(argc, argv);
	QApplication app(argc, argv);
    
	Window window(argc, argv);
	window.setWindowTitle("Boonas Viewer");
	window.show();

	return app.exec();
}
