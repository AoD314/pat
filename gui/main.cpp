
#include <QtGui/qapplication.h>
#include <QtGui/qlabel.h>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	QLabel l("hello");
	l.show();

	return app.exec();
}
