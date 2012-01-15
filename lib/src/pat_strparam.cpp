
#include "pat/pat_strparam.hpp"

namespace pat
{

	StrParams::StrParams(QString name, QString value, QString value_from, QString value_to, QString step, QString type):
	name(name), value(value), value_from(value_from),  value_to(value_to), step(step), type(type) { }

	StrParams::StrParams():name(""), value(""), value_from(""),  value_to(""), step(""), type(""){}

	QString StrParams::to_str()
	{
		QString out;
		out += "name:{" + name + "}; ";
		out += "value:{" + value + "}; ";
		out += "from:{" + value_from + "}; ";
		out += "to:{" + value_to + "}; ";
		out += "step:{" + step + "}; ";
		out += "type:{" + type + "}";

		return out;

	}

}

