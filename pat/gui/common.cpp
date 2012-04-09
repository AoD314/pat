
#include "common.hpp"

namespace pat
{
	void center_qwidget(QWidget * widget)
	{
		if(QApplication::desktop()->isFullScreen())
			return;

		int w = QApplication::desktop()->width();
		int h = QApplication::desktop()->height();
		int mw = widget->size().width();
		int mh = widget->size().height();
		int cw = (w/2) - (mw/2);
		int ch = (h/2) - (mh/2);
		widget->move(cw,ch);
	}

}
