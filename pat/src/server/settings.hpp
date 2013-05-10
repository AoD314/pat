
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <string>

#include "patconfig.hpp"

namespace pat
{
	class PAT_EXPORTS Settings
	{
		public:
			Settings(int argc, char ** argv);

			int port();

			std::string path_to_app();

		private:
			std::string path;
	};

}
#endif
