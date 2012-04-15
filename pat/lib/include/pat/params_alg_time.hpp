
#ifndef __PARAMS_ALG_TIME_HPP__
#define __PARAMS_ALG_TIME_HPP__

#include "patconfig.hpp"
#include <cstddef>

namespace pat
{
    class PAT_EXPORTS params_time
    {
        protected:
            size_t time;
        public:
            void set_time(size_t t);
    };

}

#endif

