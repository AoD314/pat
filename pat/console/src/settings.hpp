
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

		void SaveSettings();

		QString language();
		QString get_path_to_language();

		void set_win_size(QWidget * win);
		void set_language(QString language);

	private:
		QString path_to_testsystem;
		QRect geometry;
		QString path_to_lang;
		QString lang;
};

#endif

