
#ifndef __PAT_SYSTEM_HPP__
#define __PAT_SYSTEM_HPP__

#include <typeinfo>

#include "pat/convert.hpp"
#include "patconfig.hpp"

class QTcpSocket;
typedef unsigned int quint32;

namespace pat
{
	class PAT_EXPORTS System
	{
		public:
			System();
			System(const std::string & host, unsigned int port);
			void send_result(double result);

			virtual ~System();
		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
			quint32 block_size;

			void send_message_to_server(std::string cmd, std::string res);
			std::string receive_message_from_server();
	};

}

#endif
