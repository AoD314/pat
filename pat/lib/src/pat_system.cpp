
#include "pat/pat_system.hpp"

namespace pat
{
	PAT_System::PAT_System() : host("127.0.0.1"), port(13314), socket(new QTcpSocket), block_size(0)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

	PAT_System::PAT_System(const std::string & host, unsigned int port):
		host(host), port(port), socket(new QTcpSocket), block_size(0)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

	PAT_System::~PAT_System()
	{
		socket->disconnect();
		delete socket;
	}

	void PAT_System::send_message_to_server(std::string cmd, std::string var_name, std::string value_min, std::string value_max)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0) << QString(cmd.c_str()) << QString(var_name.c_str()) << QString(value_min.c_str()) << QString(value_max.c_str());
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

	void PAT_System::send_result(double result)
	{
		send_message_to_server("result", to_str(result, 0, 32), "", "");
	}

	std::string PAT_System::receive_message_from_server()
	{
		QDataStream in(socket);
		in.setVersion(QDataStream::Qt_4_7);
		block_size = 0;

		socket->waitForReadyRead();

		for (;;)
		{
			if (!block_size)
			{
				if (static_cast<size_t>(socket->bytesAvailable()) < sizeof(quint32))
				{
					break;
				}

				in >> block_size;
			}

			if (socket->bytesAvailable() < block_size)
			{
				break;
			}

			QString q_value;
			std::string value;

			in >> q_value;

			value = std::string(q_value.toUtf8().constData());

			block_size = 0;

			return value;
		}

		return "";
	}
}
