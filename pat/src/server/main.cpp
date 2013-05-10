
#include <QtGui>

#include "application.hpp"

int main(int argc, char ** argv)
{
	QCoreApplication app(argc, argv);

	pat::Application application(argc, argv);

	return app.exec();
}
