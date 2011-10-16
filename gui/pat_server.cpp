
#include "pat_server.hpp"

namespace pat
{
	PAT_Server::PAT_Server(int port) : QTcpServer(0)
	{
		block_size = 0;

		if (!this->listen(QHostAddress::Any, port))
		{
			QMessageBox::critical(0, "Server Error", "Unable to start the server : " + this->errorString());
			this->close();
			return;
		}

		connect(this, SIGNAL(newConnection()), this, SLOT(new_connection()));
	}

	void PAT_Server::send_to_client(QTcpSocket * socket, std::string value)
	{
		qDebug() << "send to client";
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);


		out << quint32(0) << QString(value.c_str());
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);
	}

	void PAT_Server::read()
	{
		qDebug() << "read client";

		QTcpSocket * client = (QTcpSocket *)sender();
		QDataStream in(client);
		in.setVersion(QDataStream::Qt_4_7);

		QString q_cmd;
		QString q_name;
		QString q_value;
		QString q_value_from;
		QString q_value_to;
		QString q_value_step;
		QString q_value_type;

		for (;;)
		{
			if (!block_size)
			{
				if (client->bytesAvailable() < sizeof(quint32))
				{
					break;
				}
				in >> block_size;
			}

			if (client->bytesAvailable() < block_size)
			{
				break;
			}

			in >> q_cmd >> q_name >> q_value >> q_value_from >>  q_value_to >> q_value_step >> q_value_type;

			QString msg = q_cmd + " " + q_name + " " + q_value;

			qDebug() << msg;

			block_size = 0;

			if (q_cmd.compare("get") == 0)
			{
				send_to_client(client, "1111");
			}
		}
	}

	void PAT_Server::new_connection()
	{
		qDebug() << "conn";
		QTcpSocket * client = this->nextPendingConnection();
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}

}
