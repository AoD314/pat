
#include "pat/gui_server.hpp"
#include "pat/pat_convert.hpp"

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
		QString str = "send to client : " + QString(value.c_str());
		log(str);

		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0) << QString(value.c_str());
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

	void PAT_Server::read()
	{
		QTcpSocket * client = (QTcpSocket *)sender();
		last_client = client;
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

			QString str = "read from client : " + q_cmd + " " + q_name + " " + q_value + " " + q_value_from + " " +  q_value_to + " " + q_value_step + " " + q_value_type;
			log(str);

			block_size = 0;

			process(q_cmd, q_name, q_value, q_value_from, q_value_to, q_value_step, q_value_type);
		}
	}

	void PAT_Server::process(QString cmd, QString name, QString value, QString value_from, QString value_to, QString step, QString type)
	{
		log("run process: " + cmd);

		if (cmd.compare("init") == 0)
		{
			init(name, value, value_from, value_to, step, type);
		}
		else if (cmd.compare("get") == 0)
		{
			get(name);
		}
		else if (cmd.compare("result") == 0)
		{
			result(from_str<double>(value.toStdString()));
		}
	}

	void PAT_Server::send_to_value(QString value)
	{
		send_to_client(last_client, value.toStdString());
	}

	void PAT_Server::new_connection()
	{
		log("new connection");
		QTcpSocket * client = this->nextPendingConnection();
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}

}
