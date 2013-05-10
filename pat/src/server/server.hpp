
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <QtNetwork>

#include "patconfig.hpp"
#include "pat/gen.hpp"
#include "pat/convert.hpp"

#include "settings.hpp"

namespace pat
{
	class PAT_EXPORTS Server : public QTcpServer
	{
		Q_OBJECT

		private:
			quint64 count_connection;
			quint32 block_size;
			QTcpSocket * last_client;

			void send_value_to_client(QTcpSocket * socket, QString value);

		public:
			Server(Settings settings);

		signals:
			void log(QString);

			void params (QString name, QString value);
			void get (QString name);
			void alg (QString name);
			void init(QString name, Gen gen);

			void result(double result);

		public slots:
			void read();
			void new_connection();
			void send_to_client(QString value);

	};

}

#endif

