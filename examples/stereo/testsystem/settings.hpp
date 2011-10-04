
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <string>
#include <opencv2/opencv.hpp>

class Settings
{
	public:
		Settings(int argc, const char ** argv);
		bool is_exit();
		~Settings();

		std::string get_gt();

	private:
		cv::CommandLineParser * parser;
		
};

#endif
