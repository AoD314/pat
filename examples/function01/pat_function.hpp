
#ifndef __PAT_FUNCTION_HPP__
#define __PAT_FUNCTION_HPP__

#include "pat/pat.hpp"

class PAT_Func : public pat::PAT_BASE
{
	public:
		PAT_Func(int argc, const char ** argv);

	protected:
		double run();
		void  init();
};

#endif
