
#ifndef __PAT_STRPARAM_HPP__
#define __PAT_STRPARAM_HPP__

#include <QtCore>

namespace pat
{
	class StrParams
	{
		public:
			QString name;
			QString value;
			QString value_from;
			QString value_to;
			QString step;
			QString type;

			StrParams(QString name, QString value, QString value_from, QString value_to, QString step, QString type);
			StrParams();

			QString to_str();
	};
}

#endif
