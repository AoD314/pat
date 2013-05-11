
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

			void send_value_to_client(QTcpSocket * socket, std::string value);

		public:
			Server(Settings settings);

		signals:
			void log(std::string message);

			void params (std::string name, std::string value);
			void get (std::string name);
			void alg (std::string name);
			void init(std::string name, Gen gen);

			void result(double result);

		public slots:
			void read();
			void new_connection();
			void send_to_client(std::string value);

	};

}

#endif

