
#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include "patconfig.hpp"
#include "pat/convert.hpp"
#include "pat/generator.hpp"

namespace pat
{

	class PAT_EXPORTS client
	{
		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
			quint32 block_size;

			void send_message_to_server(std::vector<std::string> msgs);
			void send_message_to_server(std::vector<std::string> msgs, std::vector<Number> vec);
			std::string receive_message_from_server();

		protected:
			void set_alg(std::string alg);

		public:
			client();

			template <typename T>
			T get(const std::string & name)
			{
				std::vector<std::string> msgs;
				msgs.push_back("get");
				msgs.push_back(name);
				send_message_to_server(msgs);

				return from_str<T>(receive_message_from_server());
			}

			void init(const std::string & name, Gen gen)
			{
				std::vector<std::string> msgs;
				msgs.push_back("init");
				msgs.push_back(name);
				msgs.push_back(gen.get_type());

				std::vector<Number> l = gen.get_list();
				msgs.push_back(QString::number(l.size()).toStdString());

				send_message_to_server(msgs, l);
			}


	};

}

#endif

