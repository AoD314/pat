
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

    Mat r = cv::imread(settings.right(), 0);
    Mat l = cv::imread(settings.left() , 0);

	const int max_disparity = 96;
	int iteration = 7;
	int level = 5;

	pat::PAT_System pat;

	pat.init("max_disp", 64, 96, 16, 80);
	pat.init("iter", 3, 11, 2, 5);


	StereoBeliefPropagation csbp(max_disparity, iteration, level);

    GpuMat disparity(l.size(), CV_8U);
    GpuMat left  (l);
    GpuMat right (r);

    csbp(left, right, disparity);

    Mat disp;
    disparity.download(disp);

    cv::imwrite(settings.result(), disp);

	return 0;
}
