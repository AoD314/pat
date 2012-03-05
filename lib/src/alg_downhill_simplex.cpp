
#include "pat/alg_downhill_simplex.hpp"

namespace pat
{
	PAT_Downhill_Simplex::PAT_Downhill_Simplex(SpaceParam *sp) : PAT_Algorithm(sp) {}

	void PAT_Downhill_Simplex::run()
	{
		size_t N = space_param->max_iter();
		double e = space_param->epsilon();
		size_t iter = 0;

		Point x0 = space_param->get_def();

		std::vector<FunctionND> v_fnc;
		v_fnc.push_back(function(x0));

		for (size_t i = 0; i < x0.dim(); ++i)
		{
			Point dx = x0 + 2 * x0.delta(i);
			v_fnc.push_back(function(dx));
		}

		sort(v_fnc);

		emit publish_result(v_fnc[x0.dim()]);

		/*/
		while(true)
		{

			if (iter > N || ((f1 - f0) < e))
			{
				break;
			}
		}
		//*/
	}

}

