
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_bruteforce.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{
	PAT_BruteForce::PAT_BruteForce() : params_min(), isdone(false), is_need_first_pass(true), testsystem("") {}

	void PAT_BruteForce::logging(QString msg)
	{
		log(msg);
	}

	void PAT_BruteForce::answer()
	{
		log(QString("PAT_BruteForce::answer()"));
		QString str("");

		std::vector<std::string> list = params_min.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			str += QString((*it).c_str()) + QString(" = ") + QString((params_min.get_str(*it)).c_str()) + QString("\n");
		}

		log(str);
	}

	void PAT_BruteForce::init()
	{
		log(QString("PAT_BruteForce::init()"));
		std::vector<std::string> list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			params.set_min(*it);
		}
		iter_number = 0;
	}

	void PAT_BruteForce::next_step(double value)
	{
		log(QString("PAT_BruteForce::next_step(" + QString::number(value) + ")"));
		if (params_min.minvalue > value)
		{
			params_min = params;
			params_min.minvalue = value;
		}

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

		iter_number++;
		isdone = (shift && it == list.end()) || (iter_number >= max_iters);
		publish(params_min);
		log(QString("PAT_BruteForce::next_step( is_done = " + QString::number(isdone) + ")"));
	}

	bool PAT_BruteForce::is_done()
	{
		return isdone;
	}

	void PAT_BruteForce::result(double val)
	{
		next_step(val);
	}

	void PAT_BruteForce::get(QString name)
	{
		log(QString("PAT_BruteForce::get("+ name + ") = "));
		if (is_need_first_pass == true)
		{
			is_need_first_pass = false;
			init();
		}

		std::string n = params.get_str(name.toStdString());
		log(QString("PAT_BruteForce::get.value = " + QString(n.c_str())));
		send(QString(n.c_str()));
	}

	void PAT_BruteForce::init(StrParams sp)
	{
		log(QString("PAT_BruteForce::init(" + sp.name + ")"));
		if (params.find(sp.name.toStdString())) return;
		log(QString("PAT_BruteForce::init = [" + sp.to_str() + "]"));

		std::string t(sp.type.toStdString());

		if ((t.compare("f") == 0)     ||
			(t.compare("d") == 0)     ||
			(t.compare("float") == 0) ||
			(t.compare("double") == 0))
		{
			params.add<Params::r_float>(sp.name.toStdString(),
										from_str<Params::r_float>(sp.value_from.toStdString()),
										from_str<Params::r_float>(sp.value_to.toStdString()),
										from_str<Params::r_float>(sp.step.toStdString()),
										from_str<Params::r_float>(sp.value.toStdString()));
		}
		else
		{
			params.add<Params::r_int>(sp.name.toStdString(),
									  from_str<Params::r_int>(sp.value_from.toStdString()),
									  from_str<Params::r_int>(sp.value_to.toStdString()),
									  from_str<Params::r_int>(sp.step.toStdString()),
									  from_str<Params::r_int>(sp.value.toStdString()));
		}
	}
}
