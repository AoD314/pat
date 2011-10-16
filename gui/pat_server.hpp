
#ifndef __PAT_SERVER_HPP__
#define __PAT_SERVER_HPP__

#include <QtGui>
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

namespace pat
{

	class PAT_Server : public QTcpServer
	{
		Q_OBJECT

		public:
			PAT_Server(int port);

			void send_to_client(QTcpSocket * socket, std::string value);

		private:
			quint32 block_size;

		public slots:
			void read();
			void new_connection();

	};

}

#endif
