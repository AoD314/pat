
#include "pat/pat_strparam.hpp"

namespace pat
{

	StrParams::StrParams(QString name, QString value_def, QString value_min, QString value_max):
	name(name), value_min(value_min),  value_max(value_max), value_def(value_def) { }

	StrParams::StrParams():name(""), value_def(""), value_min(""),  value_max("") {}

	QString StrParams::to_str()
	{
		QString out;
		out += "name:{" + name + "}; ";
		out += "min:{" + value_min + "}; ";
		out += "max:{" + value_max + "}; ";
		out += "def:{" + value_def + "}; ";

		return out;

	}

}

