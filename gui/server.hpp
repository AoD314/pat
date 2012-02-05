
#ifndef __PAT_SERVER_HPP__
#define __PAT_SERVER_HPP__

#include <QtGui>
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "pat/pat_params.hpp"
#include "pat/pat_strparam.hpp"

namespace pat
{
	class PAT_Server : public QTcpServer
	{
		Q_OBJECT

		public:
			PAT_Server(int port);

		private:
			Params params;
			quint32 block_size;
			QTcpSocket * last_client;

			void send_value_to_client(QTcpSocket * socket, QString value);

			void operator=(const pat::PAT_Server&);

		signals:
			void log(QString msg);

			void result(double result);
			void get(QString name);
			void init(StrParams sp);

		public slots:
			void read();
			void new_connection();
			void send_to_client(QString value);

	};

}

#endif
