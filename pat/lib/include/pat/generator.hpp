
#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include "patconfig.hpp"
#include "pat/convert.hpp"
#include "pat/number.hpp"
#include <vector>
#include <string>

namespace pat
{
    class PAT_EXPORTS Gen
    {
        private:
            std::string type;
            std::vector<Number> list;

        public:
            Gen(){}
            Gen(Number a, Number b);
            Gen(Number a, Number b, Number step);
            Gen(const std::vector<Number> & v);

            std::string get_type();
            std::vector<Number> get_list();
    };
}

#endif
