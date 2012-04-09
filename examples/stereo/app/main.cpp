
#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>

//#include "pat/pat.hpp"

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

	int max_disparity = 80;
	int iteration = 3;
	int level = 5;

	float max_data_term = 8.92494f;
	float data_weight = 0.0422628f;
	float max_disc_term = 2.58139f;
	float disc_single_jump = 0.118465f;

	/*/
	float max_data_term = 10.0f;
	float data_weight = 0.07f;
	float max_disc_term = 1.7f;
	float disc_single_jump = 1.0f;
	//*/

#ifdef use_pat_system

	pat::PAT_System pat;

	/*/
	pat.init("max_disp", 80, 112);
	pat.init("iter",  3, 15);
	pat.init("level", 3, 7);
	//*/

	pat.init("max_data_term",    6.50, 13.5);
	pat.init("data_weight",      0.01, 00.8);
	pat.init("max_disc_term",    0.05, 03.5);
	pat.init("disc_single_jump", 0.01, 03.5);
	//*/

	/*/
	max_disparity = pat.get_params<int>("max_disp");
	iteration     = pat.get_params<int>("iter");
	level         = pat.get_params<int>("level");
	//*/

	//*/
	max_data_term    = pat.get_params<double>("max_data_term");
	data_weight      = pat.get_params<double>("data_weight");
	max_disc_term    = pat.get_params<double>("max_disc_term");
	disc_single_jump = pat.get_params<double>("disc_single_jump");
	//*/

#endif

	//StereoBeliefPropagation csbp(max_disparity, iteration, level, max_data_term, data_weight, max_disc_term, disc_single_jump);
	StereoBeliefPropagation csbp;//max_disparity, iteration, level);

	GpuMat disparity(l.size(), CV_8U);
	GpuMat left  (l);
	GpuMat right (r);

	csbp(left, right, disparity);

	Mat disp;
	disparity.download(disp);

	unsigned char m = 0;
	for (size_t i = 0; i < disp.size().area(); ++i)
	{
		if (m < disp.data[i])
			m = disp.data[i];
	}
	if (m != 0)
	{
		for (size_t i = 0; i < disp.size().area(); ++i)
		{
			disp.data[i] = static_cast<unsigned char>(static_cast<float>(disp.data[i]) * 255.0 / static_cast<float>(m));
		}
	}

	cv::imwrite(settings.result(), disp);

	std::cout << "finish StereoBP" << std::endl;

	return 0;
}
