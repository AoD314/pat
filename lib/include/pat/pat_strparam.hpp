
#ifndef __PAT_STRPARAM_HPP__
#define __PAT_STRPARAM_HPP__

#include <QtCore>

#include "patconfig.hpp"

namespace pat
{
	class PAT_EXPORTS StrParams
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
