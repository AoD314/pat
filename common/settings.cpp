
#include "settings.hpp"

Settings::Settings(int argc, char ** argv)
{
	QCoreApplication::setApplicationName("pat");
	QCoreApplication::setApplicationVersion("0.0.0");

	QSettings settings("pat.config", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	lang = settings.value("main/lang", "en").toString();
	path_to_lang = settings.value("main/path_to_lang", "./trans").toString();

	geometry = settings.value("window/geometry").toRect();
}

void Settings::SaveSettings()
{
	QSettings settings("pat.config", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	settings.setValue("window/geometry", geometry);
	settings.setValue("main/lang", lang);
	settings.setValue("main/path_to_lang", path_to_lang);
}

void Settings::set_win_size(QWidget * win)
{
	geometry = win->geometry();
}

void Settings::set_language(QString language)
{
	lang = language;
}

QString Settings::get_path_to_testsystem()
{
	return path_to_testsystem;
}

QRect Settings::get_geometry_window()
{
	return geometry;
}

QString Settings::get_path_to_language()
{
	return path_to_lang;
}

QString Settings::language()
{
	return lang;
}
