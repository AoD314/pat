
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <QtGui>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

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

		QTcpServer * server;
		int port;

		void send_to_client(QTcpSocket * socket, std::string value);

	private slots:
		void read_client();
		void new_connection();

};

#endif
