
#include "pat/settings.hpp"

namespace pat
{

	Settings::Settings(int, char **)
	{}

	int Settings::port()
	{
		return 13314;
	}

	std::string Settings::path_to_app()
	{
		// FIXME: implemented path_to_app method
		return "/work/projects/pat/pat/examples/build/rozenbrok/testsystem/ts_rosenbrok";
	}

}
