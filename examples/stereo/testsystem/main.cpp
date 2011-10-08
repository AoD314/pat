
#include <iostream>
#include <algorithm>
#include <stdlib.h>

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
	cv::Mat ratio(gt.size(), CV_32FC1);

	for (int i = 0; i < ratio.cols; i++)
		for (int j = 0; j < ratio.rows; j++)
		{			
			ratio.at<float>(j, i) = static_cast<float>(gt.at<char>(j, i)) / ((static_cast<float>(disp.at<char>(j, i)) == 0) ? 1 : static_cast<float>(disp.at<char>(j, i)));
		}

	float M = 0;

	for (int i = 0; i < ratio.cols; i++)
		for (int j = 0; j < ratio.rows; j++)
		{
			M += ratio.at<float>(j, i);
		}

	M /= (ratio.cols * ratio.rows); 

	float D = 0;

	for (int i = 0; i < ratio.cols; i++)
		for (int j = 0; j < ratio.rows; j++)
		{
			D += (ratio.at<float>(j, i) - M);
		}

	D /= (ratio.cols * ratio.rows); 

	cout << "M : " << M << endl;
	cout << "D : " << D << endl;

	for (int i = 0; i < ratio.cols; i++)
		for (int j = 0; j < ratio.rows; j++)
		{
			float val = static_cast<float>(disp.at<char>(j, i));
			val = ((val * M) > 255) ? 255 : (val * M);
			disp.at<char>(j, i) = static_cast<char>(val);
		}

	disp = disp.colRange(35, disp.cols - 1);
	gt   = gt.colRange  (35, gt.cols - 1);

	disp = disp.rowRange(1, disp.rows - 1);
	gt   = gt.rowRange  (1, gt.rows - 1);

	/*
	cv::imshow("disp", disp);
	cv::imshow("gt", gt);
	cv::waitKey();
	*/

	return cv::norm(disp, gt);
}

int main(int argc, const char ** argv)
{
	Settings settings(argc, argv);
	if (settings.is_exit()) return 0;

	std::vector<std::string> list;

	//list = cv::Directory::GetListFiles(settings.get_gt(), ".png");
	list.push_back("aloe_l.png");

	get_list_name_dataset(list);

	double total_err = 0;

	std::vector<std::string>::const_iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		std::string cmd = "stereobp.exe -r=" + *it + "_r.png -l=" + *it + "_l.png --result=res.png";
		std::string gts = *it + "_gl.png";

		cout << "run : " << cmd << endl;
		int ret = system(cmd.c_str());
		cout << "ret : " << ret << endl;
		
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
		
		total_err += calc_err(gt, disp);
	}

	cout << "total error is : " << total_err << endl;

	return 0;
}
