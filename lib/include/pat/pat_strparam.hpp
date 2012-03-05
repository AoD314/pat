
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
			QString value_def;
			QString value_min;
			QString value_max;

			StrParams(QString name, QString value_def, QString value_min, QString value_max);
			StrParams();

			QString to_str();
	};
}

#endif
