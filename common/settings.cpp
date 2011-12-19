
#include "settings.hpp"

Settings::Settings(int argc, char ** argv)
{
	QCoreApplication::setApplicationName("pat");
	QCoreApplication::setApplicationVersion("0.0.0");

	QSettings settings("pat.config", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	#ifdef WIN32
		//path_to_testsystem = "C:/work/pat/examples/build/bin/testsystem.exe";
		path_to_testsystem = settings.value("/win/path_to_testsystem").toString();
	#else
		//path_to_testsystem = "/work/projects/pat/pat/examples/build-stereo/bin/testsystem";
		path_to_testsystem = settings.value("/lin/path_to_testsystem").toString();
	#endif

	geometry = settings.value("window/geometry").toRect();
}

void Settings::SaveSettings(QWidget * win)
{
	QSettings settings("pat.config", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");
	settings.setValue("window/geometry", win->geometry());
}

QString Settings::get_path_to_testsystem()
{
	return path_to_testsystem;
}

QRect Settings::get_geometry_window()
{
	return geometry;
}
