
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <string>
#include <opencv2/opencv.hpp>

class Settings
{
	public:
		Settings(int argc, const char ** argv);

		size_t get_size();
		bool   is_exit();

		~Settings();

	private:
		cv::CommandLineParser * parser;
		
};

#endif
