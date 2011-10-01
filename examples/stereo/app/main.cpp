
#include <iostream>
#include <opencv2/opencv.hpp>

#include "settings.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char ** argv)
{
	Settings settings(argc, argv);
	if (settings.is_exit()) return 0;

	cout << "get_size : " << settings.get_size() << endl;
	

	return 0;
}
