
#include "pat/alg_downhill_simplex.hpp"
#include "pat/pat_convert.hpp"

namespace pat
{
	PAT_Downhill_Simplex::PAT_Downhill_Simplex() {}


	void PAT_Downhill_Simplex::next_step(double value)
	{
		// create simplex
		if (mode != params.dim())
		{
			params.minvalue = value;
			res.push_back(params);

			params = params_def;
			params.modify_add(list.at(mode), params.get_step<double>(list.at(mode)));
		}
		else if (mode == params.dim()) // sort test result
		{
			for (int i = 0; i < params.dim(); i++)
			{
				for (int j = 0; j < params.dim() - 1; j++)
				{
					if (res[j].minvalue < res[j+1].minvalue)
					{
						Params tmp = res[j];
						res[j] = res[j+1];
						res[j+1] = tmp;
					}
				}
			}
		}

		if (mode >= params.dim())
		{
			Params x_c = res.at(0);

			for (int i = 0; i < x_c.dim(); i++)
				x_c += res.at(i + 1);

			x_c /= x_c.dim();
			Params x_h = res.at(0);
			Params x_r = (1 + alpha) * x_c + alpha * x_h;
			params = x_r;
		}

		//else
		{


			publish(params);

			iter_number++;
			if (iter_number >= max_iters)
				isdone = true;
		}
		mode++;

		log(QString("PAT_Downhill_Simplex::next_step( is_done = " + QString::number(isdone) + ")"));
	}


	void PAT_Downhill_Simplex::logging(QString msg)
	{
		log(msg);
	}

	void PAT_Downhill_Simplex::answer()
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

	void PAT_Downhill_Simplex::init()
	{
		log(QString("Downhill Simplex alg is INIT()"));
		list = params.get_list_params();
		std::vector<std::string>::iterator it;
		for(it = list.begin(); it != list.end(); ++it)
		{
			params.set_def(*it);
		}

		params_def = params;

		MIN = std::numeric_limits<double>::max();
		mode = 0;
		res.resize(1 + params.dim());
		iter_number = 0;
	}

	bool PAT_Downhill_Simplex::is_done()
	{
		return isdone;
	}

	void PAT_Downhill_Simplex::result(double val)
	{
		next_step(val);
	}

	void PAT_Downhill_Simplex::get(QString name)
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

	void PAT_Downhill_Simplex::init(StrParams sp)
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

