
#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>

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

    StereoBeliefPropagation csbp(96, 7, 5);

    GpuMat disparity(l.size(), CV_8U);
    GpuMat left  (l);
    GpuMat right (r);

    csbp(left, right, disparity);

    Mat disp;
    disparity.download(disp);

    cv::imwrite(settings.result(), disp);

	return 0;
}
