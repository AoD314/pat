
#ifndef __GR_HPP__
#define __GR_HPP__

#include "patconfig.hpp"

#include "pat/params_alg_time.hpp"
#include "pat/params_alg_n.hpp"
#include "pat/params_alg_eps.hpp"
#include "pat/params_alg_x.hpp"
#include "pat/client.hpp"

namespace pat
{
    class PAT_EXPORTS GR : public client, public params_time, public params_n, public params_x, public params_eps
    {
        public:
            GR();
    };
}

#endif
