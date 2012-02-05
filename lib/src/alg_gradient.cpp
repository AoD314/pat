
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_gradient.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{
	PAT_Gradient::PAT_Gradient()
	{
		is_need_first_pass = true;
		max_iters = std::numeric_limits<size_t>::max();
		iter_number = 0;
	}

	void PAT_Gradient::logging(QString msg)
	{
		log(msg);
	}

	void PAT_Gradient::answer()
	{
		QString str("");

		std::vector<std::string> list = params_min.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			str += QString((*it).c_str()) + QString(" = ") + QString((params_min.get_str(*it)).c_str()) + QString("\n");
		}
		qDebug() << str;

		log(str);
	}

	void PAT_Gradient::init()
	{
		log(QString("gradient alg is INIT()"));
		list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			params.set_def(*it);
		}

		params_point = params;

		MIN = std::numeric_limits<double>::max();
		lambda = 128.0;
		mode = 0;
		res.resize(1 + params.dim());
		iter_number = 0;
	}

	void PAT_Gradient::next_step(double value)
	{
		res.at(mode) = value;

		if (mode == params.dim())
		{
			params = params_point;
			std::string name;

			if (abs(lambda - 128.0) < 0.00025)
			{
				// calculate lambda
				lambda = 0;
				for(size_t i = 0; i < params.dim(); ++i)
				{
					name = list.at(i);
					lambda += ((params.get_step<double>(name) * params.get_step<double>(name))/ abs(res.at(i + 1) - res.at(0)));
				}
				lambda /= params.dim();
			}

			log(QString("\nUSE new lambda: " + QString::number(lambda)) + "\n");

			for(size_t i = 0; i < params.dim(); ++i)
			{
				name = list.at(i);
				params.modify_add(name, (-lambda) * (res.at(i + 1) - res.at(0)) / params.get_step<double>(name));
			}

			publish(params);

			res.clear();
			res.resize(1 + params.dim());
			lambda *= 0.5;
			mode = 0;
			params_point = params;
			iter_number++;
			if (iter_number >= max_iters)
				isdone = true;
			return;
		}

		std::string name = list.at(mode);
		params = params_point;
		params.next(name);
		mode++;
		log(QString("PAT_Gradient::next_step( is_done = " + QString::number(isdone) + ")"));
	}

	bool PAT_Gradient::is_done()
	{
		return isdone;
	}

	void PAT_Gradient::result(double val)
	{
		next_step(val);
	}

	void PAT_Gradient::get(QString name)
	{
		if (is_need_first_pass == true)
		{
			is_need_first_pass = false;
			init();
		}

		std::string n = params.get_str(name.toStdString());
		log(QString("ALG : slot get(" + QString(name) + ") = " + QString(n.c_str()) ));
		send(QString(n.c_str()));
	}

	void PAT_Gradient::init(StrParams sp)
	{
		log(QString("ALG : slot init(" + sp.name + ")"));
		if (params.find(sp.name.toStdString())) return;
		log(QString("ALG : slot init = [" + sp.to_str() + "]"));

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



