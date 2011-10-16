
#include <stdlib.h>
#include <string>
#include <iostream>

#include <QtGui/qapplication.h>
#include "mainwindow.hpp"

using pat::MainWindow;

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	MainWindow main_windows;
	main_windows.show();

	return app.exec();
}
