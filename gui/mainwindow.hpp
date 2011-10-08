
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <QtGui>

class MainWindow : public QWidget
{
	Q_OBJECT

	public:
		MainWindow(QWidget * parent = 0);

	private:
		QHBoxLayout * layout_h;
		QVBoxLayout * layout_v;

		QTextEdit    * edit;
		QPushButton  * button;
		QTextBrowser * text;

};

#endif
