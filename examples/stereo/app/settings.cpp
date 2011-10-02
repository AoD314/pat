
#include "settings.hpp"

#include <opencv2/opencv.hpp>

const char * help = 
{
    "{ h |  help  | false                                                    | this message }"
    "{ l |  left  |/work/projects/pat/pat/examples/stereo/dataset/aloe_l.png | left image   }"
    "{ r | right  |/work/projects/pat/pat/examples/stereo/dataset/aloe_r.png | right image  }"
    "{   | result |/work/projects/pat/pat/examples/stereo/dataset/result.png | result image = disparity }"
};

Settings::Settings(int argc, const char ** argv)
{
	parser = new cv::CommandLineParser(argc, argv, help);
}

Settings::~Settings()
{
	delete parser;
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

std::string Settings::left()
{
    return parser->get<std::string>("l");
}

std::string Settings::right()
{
    return parser->get<std::string>("r");
}

std::string Settings::result()
{
    return parser->get<std::string>("result");
}
