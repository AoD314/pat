
#include "pat/client.hpp"

namespace pat
{
	client::client()
	{
		port = 13314;
		socket = new QTcpSocket;
		socket->connectToHost(QHostAddress(QString::fromUtf8("127.0.0.1")), port);
	}

	std::string client::receive_message_from_server()
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

	void client::set_alg(std::string alg)
	{
		std::vector<std::string> msgs;
		msgs.push_back("alg");
		msgs.push_back(alg);

		send_message_to_server(msgs);
	}

	void client::send_message_to_server(std::vector<std::string> msgs)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0);

		for(size_t i = 0; i < msgs.size(); ++i)
		{
			out << QString(msgs.at(i).c_str());
		}

		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

	void client::send_message_to_server(std::vector<std::string> msgs, std::vector<Number> vec)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0);

		for(size_t i = 0; i < msgs.size(); ++i)
		{
			out << QString(msgs.at(i).c_str());
		}

		for(size_t i = 0; i < vec.size(); ++i)
		{
			out << vec.at(i);
		}

		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}


}
