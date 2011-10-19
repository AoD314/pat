
#ifndef __PAT_SERVER_HPP__
#define __PAT_SERVER_HPP__

#include <QtGui>
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "pat/params.hpp"

namespace pat
{

	class PAT_Server : public QTcpServer
	{
		Q_OBJECT

		public:
			PAT_Server(int port);

			void send_to_client(QTcpSocket * socket, std::string value);


		private:
			Params params;
			quint32 block_size;

			void process(QTcpSocket * client, QString cmd, QString name, QString value, QString value_from, QString value_to, QString step, QString type);

		signals:
			void log(QString msg);
			void result(double result);
			void get(QTcpSocket * client, QString name);

		public slots:
			void read();
			void new_connection();
			void send_to_value(QTcpSocket * client, QString value);

	};

}

#endif
