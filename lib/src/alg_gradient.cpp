
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
	}

	void PAT_Gradient::log(QString msg)
	{
		logging(msg);
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

		logging(str);
	}

	void PAT_Gradient::init()
	{
		logging(QString("gradient alg is INIT()"));
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
	}

	void PAT_Gradient::next_step(double value)
	{
		res.at(mode) = value;

		if (mode == params.dim())
		{
			logging(QString("recalc new point(params)"));
			params = params_point;
			std::string name;

			if (abs(lambda - 128.0) < 0.0000025)
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

			qDebug() << "use new lambda: " << lambda;

			for(size_t i = 0; i < params.dim(); ++i)
			{
				name = list.at(i);
				params.modify_add(name, (-lambda) * (res.at(i + 1) - res.at(0)) / params.get_step<double>(name));
			}

			qDebug() << "end ====== point(params)";
			res.clear();
			lambda *= 0.5;
			mode = 0;
			params_point = params;
			return;
		}

		std::string name = list.at(mode);
		params = params_point;
		params.next(name);
		mode++;
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
		qDebug() << "ALG : slot get(" << name << ") = " << QString(n.c_str());
		send(QString(n.c_str()));
	}

	void PAT_Gradient::init(QString name, QString value, QString value_from, QString value_to, QString step, QString type)
	{
		logging(QString("ALG : slot init(" + name + ")"));
		if (params.find(name.toStdString())) return;
		logging(QString("ALG : slot init = [" + value + " " + value_from + " " + value_to + " " + step + " " + type + "]"));

		std::string t(type.toStdString());

		if ((t.compare("f") == 0)     ||
			(t.compare("d") == 0)     ||
			(t.compare("float") == 0) ||
			(t.compare("double") == 0))
		{
			params.add<Params::r_float>(name.toStdString(),
										from_str<Params::r_float>(value_from.toStdString()),
										from_str<Params::r_float>(value_to.toStdString()),
										from_str<Params::r_float>(step.toStdString()),
										from_str<Params::r_float>(value.toStdString()));
			logging(QString("added to float"));
		}
		else
		{
			params.add<Params::r_int>(name.toStdString(),
									  from_str<Params::r_int>(value_from.toStdString()),
									  from_str<Params::r_int>(value_to.toStdString()),
									  from_str<Params::r_int>(step.toStdString()),
									  from_str<Params::r_int>(value.toStdString()));
			logging(QString("added to int"));
		}
	}
}



