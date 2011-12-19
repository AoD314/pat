
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <QtCore>
#include <QSettings>
#include "QWidget"

class Settings
{
	public:
		Settings(int argc, char ** argv);

		QString get_path_to_testsystem();
		QRect   get_geometry_window();

		void SaveSettings(QWidget * win);

	private:
		QString path_to_testsystem;
		QRect geometry;
};

#endif

