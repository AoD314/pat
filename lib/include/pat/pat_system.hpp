
#ifndef __PAT_SYSTEM_HPP__
#define __PAT_SYSTEM_HPP__

#include <typeinfo>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include "pat/pat_convert.hpp"
#include "patconfig.hpp"

namespace pat
{
	class PAT_EXPORTS PAT_System
	{
		public:
			PAT_System();
			PAT_System(const std::string & host, unsigned int port);
			~PAT_System();

			template <typename T>
			T get_params(const std::string & name)
			{
				send_message_to_server("get", name, "", "", "", "", "");
				return from_str<T>(receive_message_from_server());
			}

			template <typename T>
			void init(const std::string & name, T min_value, T max_value, T step, T start_value)
			{
				send_message_to_server("init", name, to_str(start_value), to_str(min_value), to_str(max_value), to_str(step), typeid(step).name());
			}

			void send_result(double result);

		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
			quint32 block_size;

			void send_message_to_server(std::string cmd, std::string var_name, std::string value, std::string value_from, std::string value_to, std::string value_step, std::string value_type);
			std::string receive_message_from_server();
	};

}

#endif
