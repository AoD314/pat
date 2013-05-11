
#include <QtGui>

#include "application.hpp"

int main(int argc, char ** argv)
{
	QCoreApplication app(argc, argv);

	pat::Application application(argc, argv);
	QObject::connect(&application, SIGNAL(quit()), &app, SLOT(quit()));


	return app.exec();
}
