
#include <iostream>
#include <algorithm>

#include <opencv2/opencv.hpp>

#include "settings.hpp"

using std::cout;
using std::cin;
using std::endl;

void uniq(std::vector<std::string> & list)
{
	if (list.size() <= 0) return;

	std::string prev = list[0];

	for (size_t i = 1; i < list.size();)
	{
		if (prev.compare(list[i]) == 0)
		{
			list.erase( list.begin() + i, list.begin() + i + 1);
		}
		else
		{
			prev = list[i];
			i++;
		}
	}
}

void get_list_name_dataset(std::vector<std::string> & list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		size_t pos = list[i].find_last_of("_");
		if (pos != std::string::npos)
		{
			list[i].erase(pos);
		}		
	}

	std::sort(list.begin(), list.end());
	uniq(list);
}

int main(int argc, const char ** argv)
{
	Settings settings(argc, argv);
	if (settings.is_exit()) return 0;

	std::vector<std::string> list = cv::Directory::GetListFiles(settings.get_gt(), "*.png");

	get_list_name_dataset(list);

	std::vector<std::string>::const_iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		std::string cmd = "stereobp -r=" + *it + "_r.png -l=" + *it + "_l.png --result=res.png";
		cout << "run : " << cmd << endl;
		system(cmd.c_str());
		
		// analyze

	}
	

	return 0;
}
