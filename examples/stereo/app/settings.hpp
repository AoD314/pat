
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <string>
#include <opencv2/opencv.hpp>

class Settings
{
	public:
		Settings(int argc, const char ** argv);

                bool is_exit();

                std::string left();
                std::string right();
                std::string result();

		~Settings();

	private:
		cv::CommandLineParser * parser;
		
};

#endif
