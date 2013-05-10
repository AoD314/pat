
#include <iostream>

#include "settings.hpp"


namespace pat
{
	Settings::Settings(int argc, char ** argv)
	{
		if (argc > 1)
		{
			path = std::string(argv[1]);
		}
		else
		{
			path = "";
		}

		std::cout << "settings.path: [" << path << "]" << std::endl;
	}

	int Settings::port()
	{
		return 13314;
	}

	std::string Settings::path_to_app()
	{
		return path;
	}

}
