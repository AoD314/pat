
#ifndef __RND_HPP__
#define __RND_HPP__

#include "patconfig.hpp"

#include "pat/params_alg_time.hpp"
#include "pat/params_alg_n.hpp"
#include "pat/client.hpp"

namespace pat
{
    class PAT_EXPORTS RND : public client, public params_time, public params_n
    {
        public:
            RND();
    };
}

#endif
