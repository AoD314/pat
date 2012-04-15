
#ifndef __PARAMS_ALG_EPS_HPP__
#define __PARAMS_ALG_EPS_HPP__

#include "patconfig.hpp"

namespace pat
{
    class PAT_EXPORTS params_eps
    {
        protected:
            double eps;
        public:
            void set_eps(double e);
    };
}

#endif

