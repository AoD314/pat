
#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "pat/alg_bruteforce.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{
	PAT_BruteForce::PAT_BruteForce()
	{
		is_need_first_pass = true;
	}

	void PAT_BruteForce::log(QString msg)
	{
		logging(msg);
	}

	void PAT_BruteForce::answer()
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

	void PAT_BruteForce::init()
	{
		logging(QString("PAT_BruteForce::init()"));
		std::vector<std::string> list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			params.set_min(*it);
		}

		MIN = std::numeric_limits<double>::max();
	}

	void PAT_BruteForce::next_step(double value)
	{
		logging(QString("PAT_BruteForce::next_step(" + QString::number(value) + ")"));
		if (MIN > value)
		{
			MIN = value;
			params_min = params;
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

		isdone = (shift && it == list.end());
		logging(QString("PAT_BruteForce::next_step( is_done = " + QString::number(isdone) + ")"));
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
		if (is_need_first_pass == true)
		{
			is_need_first_pass = false;
			init();
		}

		std::string n = params.get_str(name.toStdString());
		logging(QString("PAT_BruteForce::get("+ name + ") = " + n.c_str()));
		send(QString(n.c_str()));
	}

	void PAT_BruteForce::init(QString name, QString value, QString value_from, QString value_to, QString step, QString type)
	{
		logging(QString("PAT_BruteForce::init("+ name + ") = " + value));
		if (params.find(name.toStdString())) return;

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
		}
		else
		{
			params.add<Params::r_int>(name.toStdString(),
									  from_str<Params::r_int>(value_from.toStdString()),
									  from_str<Params::r_int>(value_to.toStdString()),
									  from_str<Params::r_int>(step.toStdString()),
									  from_str<Params::r_int>(value.toStdString()));
		}
	}
}
