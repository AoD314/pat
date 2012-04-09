
#include "pat/pat_strparam.hpp"

namespace pat
{

    StrParams::StrParams(QString name, QString value_min, QString value_max):
    name(name), value_min(value_min),  value_max(value_max) { }

    StrParams::StrParams():name(""), value_min(""),  value_max("") {}

	QString StrParams::to_str()
	{
		QString out;
		out += "name:{" + name + "}; ";
		out += "min:{" + value_min + "}; ";
		out += "max:{" + value_max + "}; ";

		return out;

	}

}

