
#include "pat/pat_base.hpp"
#include "pat/pat_convert.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

namespace pat
{

	void PAT_BASE::set_max_time(size_t sec)
	{
		max_time = sec;
	}

	void PAT_BASE::set_max_iter(size_t iter)
	{
		max_iter = iter;
	}

	void PAT_BASE::set_precision(double p)
	{
		precision = p;
	}

	void PAT_BASE::print_info()
	{
		std::vector<std::string> list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			std::cout << (*it) << " = " << params.get<double>(*it) << "\n";
		}
	}

	void PAT_BASE::run_auto_tune() 
	{
		init();
		std::cout << "MAX iter : " << max_iter << std::endl; 
		std::cout << "MAX time : " << max_time << std::endl; 

		Params cparams;

		size_t current_iter = 0;
		double MAX = -std::numeric_limits<double>::max();

		/* reset each value */

		std::vector<std::string> list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			params.set_min(*it);
		}

		while (current_iter <= max_iter && next_params())
		{
			std::cout << "iter : " << to_str(current_iter, 6) << "   ";

			double val = run();
			std::cout << "value: " << val << std::endl;

			if (val > MAX)
			{
				MAX = val;
				cparams = params;
			}
			current_iter++;
		}

		params = cparams;
		std::cout << "MAX : " << MAX << "\n";
	}

	bool PAT_BASE::next_params()
	{
		bool shift = false;

		std::vector<std::string> list = params.get_list_params();
		std::vector<std::string>::iterator it;

		for(it = list.begin(); it != list.end(); ++it)
		{
			params.next(*it);

			if (params.more_max(*it))
			{
				shift = true;
				params.set_min(*it);
			}
			else
				shift = false;

			if (shift == false)
			{
				break;
			}
		}	

		return !(shift && it == list.end());
	}

}
