
#ifndef __PAT_SYSTEM_HPP__
#define __PAT_SYSTEM_HPP__

#include <typeinfo>

#include "patconfig.hpp"

#include "pat/convert.hpp"

class QTcpSocket;

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
			unsigned int block_size;

			void send_message_to_server(std::string cmd, std::string res);
			std::string receive_message_from_server();
	};

}

#endif
