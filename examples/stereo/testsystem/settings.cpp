
#include "settings.hpp"

#include <opencv2/opencv.hpp>

const char * help = 
{
	"{ h  | help        | false | this message}"
	"{ gt | groundtruth |   .   | folder with ground truth of disparity }"
};

Settings::Settings(int argc, const char ** argv)
{
	parser = new cv::CommandLineParser(argc, argv, help);
}

Settings::~Settings()
{
	delete parser;
}

std::string Settings::get_gt()
{
	return parser->get<std::string>("gt");
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