
#include "pat/pat.hpp"

namespace pat
{
	PAT_System::PAT_System() : host("127.0.0.1"), port(13314), socket(new QTcpSocket)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

	PAT_System::PAT_System(const std::string & host, unsigned int port): host(host), port(port), socket(new QTcpSocket)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

	PAT_System::~PAT_System()
	{
		socket->disconnect();
		delete socket;
	}

	void PAT_System::send_message_to_server(std::string cmd, std::string var_name, std::string value, std::string value_from, std::string value_to, std::string value_step, std::string value_type)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0) << QString(cmd.c_str()) << QString(var_name.c_str()) << QString(value.c_str()) << QString(value_from.c_str()) << QString(value_to.c_str()) << QString(value_step.c_str()) <<  QString(value_type.c_str());
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		qDebug() << "send message to server : " << socket->isOpen();
		qDebug() << " name    : " << socket->peerName();
		qDebug() << " address : " << socket->peerAddress();
		qDebug() << " port    : " << socket->peerPort();
		qDebug() << "size : " << quint32(arr_block.size() - sizeof(quint32));

		int ret = socket->write(arr_block);

		socket->waitForReadyRead(1000);

		qDebug() << "writed ! : " << ret;
	}

	void PAT_System::send_result(double result)
	{
		send_message_to_server("result", "", to_str(result), "", "", "", "");
	}

	std::string PAT_System::receive_message_from_server()
	{
		qDebug() << "receive message from server : " << socket->isOpen();

		QDataStream in(socket);
		in.setVersion(QDataStream::Qt_4_7);
		block_size = 0;

		for (;;)
		{
			qDebug() << " TRY ";
			if (!block_size)
			{
				qDebug() << "bytesAvailable : " << socket->bytesAvailable();

				if (socket->bytesAvailable() < sizeof(quint32))
				{
					break;
				}

				in >> block_size;
			}

			qDebug() << "block_size : " << block_size;

			if (socket->bytesAvailable() < block_size)
			{
				break;
			}

			QString q_value;
			std::string value;

			in >> q_value;

			qDebug() << "value : " << q_value;

			value = std::string(q_value.toUtf8().constData());

			block_size = 0;

			return value;
		}
		return "";
	}
}
