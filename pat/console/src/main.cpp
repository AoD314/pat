
#include <QtGui>

#include "pat/pat.hpp"

int main(int argc, char ** argv)
{
	QCoreApplication app(argc, argv);

	pat::Application pat_app(argc, argv);

	return app.exec();
}

