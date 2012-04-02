
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include "pat/pat.hpp"

#include "settings.hpp"

using std::cout;
using std::cin;
using std::endl;

void rum_cmd(std::string app_name, std::string args)
{
	std::string cmd;

	#ifdef WIN32
		cmd = app_name + ".exe ";
	#else
		cmd = "./" + app_name + " ";
	#endif

	cmd += args;

	system(cmd.c_str());
}

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

void print_vec(std::vector<std::string> & list)
{
	cout << "---" << endl;
	std::vector<std::string>::const_iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << "---" << endl;
}

void get_list_name_dataset(std::vector<std::string> & list)
{
	for (size_t i = 0; i < list.size();)
	{
		size_t pos = list[i].find_last_of("_");
		if (pos != std::string::npos)
		{
			list[i].erase(pos);
			i++;
		}
		else
		{
			list.erase(list.begin() + i, list.begin() + i + 1);
		}
	}

	std::sort(list.begin(), list.end());
	uniq(list);
}

double calc_err(cv::Mat gt, cv::Mat disp)
{
	double err = 0;
	size_t N = 0;
	size_t good_pixels = 0;

	//*/
	// calculate total number of valid pixel
	for (size_t i = 0; i < gt.total(); ++i)
	{
		if (gt.data[i] > 0)
		{
			++N;
			err += std::pow(disp.data[i] - gt.data[i], 2);
		}
	}

	err = std::sqrt(err / N);
	//*/

	/*/
	for (size_t i = 0; i < gt.total(); ++i)
	{
		if (gt.data[i] > 0)
		{
			++N;
			if (abs(disp.data[i] - gt.data[i]) > 1)
				good_pixels += 1;
		}
	}

	err = static_cast<double>(good_pixels) / static_cast<double>(N);
	//*/

	return err;
}

int main(int argc, const char ** argv)
{
	Settings settings(argc, argv);
	if (settings.is_exit()) return 0;

	std::cout << "start  test_system" << std::endl;

	std::vector<std::string> list;
	//list = cv::Directory::GetListFiles(settings.get_gt(), ".png");
	//list.push_back("aloe_l.png");
	//list.push_back("baby_l.png");
	list.push_back("tsukuba_l.png");

	get_list_name_dataset(list);

	double total_err = 0;

	std::vector<std::string>::const_iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		std::string args = "-r=" + *it + "_r.png -l=" + *it + "_l.png --result=res.png";
		std::string gts = *it + "_gl.png";

		cout << "run : " << "stereobp " << args << endl;
		rum_cmd("stereobp", args);

		// analyze

		// load ground truth
		cout << "read gt : " << gts << endl;
		cv::Mat gt = cv::imread(gts, 0);
		if (gt.empty())
		{
			cout << "can't read " << gts << endl;
			return -1;
		}

		// load result (disparity)
		cv::Mat disp = cv::imread("res.png", 0);

		double current_err = calc_err(gt, disp);
		std::cout << "current error is : " << current_err << std::endl;
		total_err += current_err;
	}

	cout << "total error is : " << total_err << endl;

	pat::PAT_System pat;
	pat.send_result(total_err);

	std::cout << "finish test_system" << std::endl;

	return 0;
}
