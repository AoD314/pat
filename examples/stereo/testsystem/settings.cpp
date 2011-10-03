
#include "settings.hpp"

#include <opencv2/opencv.hpp>

const char * help = 
{
	"{|help | false | this message}"
	"{ s | size | 1     | count dataset}"
	"{b|boost}"
	"{k}"
};

Settings::Settings(int argc, const char ** argv)
{
	parser = new cv::CommandLineParser(argc, argv, help);
	//parser->printParams();
}

Settings::~Settings()
{
	delete parser;
}

size_t Settings::get_size()
{
	return parser->get<size_t>("size");
}

bool Settings::is_exit()
{
	if (parser->get<bool>("help"))
	{
		parser->printParams();
		return true; 
	}
	return false;
}