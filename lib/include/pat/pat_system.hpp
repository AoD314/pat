
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
			virtual ~PAT_System();

			template <typename T>
			T get_params(const std::string & name)
			{
				send_message_to_server("get", name, "", "", "");
				return from_str<T>(receive_message_from_server());
			}

			template <typename T>
			void init(const std::string & name, T min_value, T max_value, T def_value)
			{
				send_message_to_server("init", name, to_str(min_value), to_str(max_value), to_str(def_value));
			}

			void send_result(double result);

		private:
			std::string  host;
			unsigned int port;
			QTcpSocket * socket;
			quint32 block_size;

			void send_message_to_server(std::string cmd, std::string var_name, std::string value_min, std::string value_max, std::string value_def);
			std::string receive_message_from_server();
	};

}

#endif
