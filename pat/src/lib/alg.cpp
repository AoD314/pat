
#include "pat/alg.hpp"

#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork/qhostaddress.h>

namespace pat
{
	Alg::Alg(PAT_ALGORITHM alg)
	{
		port = 13314;
		socket = new QTcpSocket;
		socket->connectToHost(QHostAddress(QString::fromUtf8("127.0.0.1")), port);

		std::vector<std::string> msgs;
		msgs.push_back("alg");
		switch(alg)
		{
            case PAT_ALG_RND:
				msgs.push_back("rnd");
				break;
            case PAT_ALG_BF:
				msgs.push_back("bf");
				break;
            case PAT_ALG_GR:
				msgs.push_back("gr");
				break;
            case PAT_ALG_DHS:
				msgs.push_back("dhs");
				break;
		}
		send_message_to_server(msgs);
	}

	void Alg::init(const std::string & name, Gen gen)
	{
		std::vector<std::string> msgs;
		msgs.push_back("init");
		msgs.push_back(name);
		msgs.push_back(gen.get_type());

		std::vector<Number> l = gen.get_list();
		msgs.push_back(QString::number(l.size()).toStdString());

		send_message_to_server(msgs, l);
	}

	void Alg::send_message_to_server(std::vector<std::string> msgs)
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

	void Alg::send_message_to_server(std::vector<std::string> msgs, std::vector<Number> vec)
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

	std::string Alg::receive_message_from_server()
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

	void Alg::set_n(size_t n)
	{
		std::vector<std::string> msgs;
		msgs.push_back("params");
		msgs.push_back("n");
		msgs.push_back(to_str<size_t>(n));
		send_message_to_server(msgs);
	}

}
