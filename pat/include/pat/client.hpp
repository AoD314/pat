
#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "patconfig.hpp"
#include "pat/convert.hpp"
#include "pat/generator.hpp"

class QTcpSocket;
class QString;
typedef unsigned int quint32;

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

			void init(const std::string & name, Gen gen);

	};

}

#endif

