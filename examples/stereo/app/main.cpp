
#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>

#include "pat/pat.hpp"

#include "settings.hpp"

using cv::Mat;
using cv::gpu::GpuMat;
using cv::gpu::StereoBeliefPropagation;

int main(int argc, const char ** argv)
{
	Settings settings(argc, argv);
	if (settings.is_exit()) return 0;

	std::cout << "start  StereoBP" << std::endl;

    Mat r = cv::imread(settings.right(), 0);
    Mat l = cv::imread(settings.left() , 0);

	int max_disparity = 96;
	int iteration = 9;
	int level = 5;

#ifdef use_pat_system

	pat::PAT_System pat;

	//pat.init("max_disp", 80, 96, 16, 80);
	pat.init("iter",  1, 31, 1, 11);
	pat.init("level", 3,  7, 1, 5);

	//max_disparity = pat.get_params<int>("max_disp");
	iteration     = pat.get_params<int>("iter");
	level         = pat.get_params<int>("level");

#endif

	StereoBeliefPropagation csbp(max_disparity, iteration, level);

    GpuMat disparity(l.size(), CV_8U);
    GpuMat left  (l);
    GpuMat right (r);

    csbp(left, right, disparity);

    Mat disp;
    disparity.download(disp);

    cv::imwrite(settings.result(), disp);

	std::cout << "finish StereoBP" << std::endl;

	return 0;
}
