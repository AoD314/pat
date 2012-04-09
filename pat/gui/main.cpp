
#include <stdlib.h>
#include <string>
#include <iostream>

#include <QtGui/qapplication.h>

#include "mainwindow.hpp"
#include "settings.hpp"

#include "pat/number.hpp"
#include "pat/point.hpp"

using pat::MainWindow;
using pat::Number;
using pat::Point;

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	Settings * settings = new Settings(argc, argv);

	MainWindow main_windows(settings);
	main_windows.show();

	return app.exec();
}
