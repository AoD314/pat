
#include "pat_server.hpp"
#include "pat/convert.hpp"

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

			process(client, q_cmd, q_name, q_value, q_value_from, q_value_to, q_value_step, q_value_type);
		}
	}

	void PAT_Server::process(QTcpSocket * client, QString cmd, QString name, QString value, QString value_from, QString value_to, QString step, QString type)
	{
		std::string t(type.toStdString());

		if (cmd.compare("init") == 0)
		{
			if ((t.compare("f") == 0)     ||
				(t.compare("d") == 0)     ||
				(t.compare("float") == 0) ||
				(t.compare("double") == 0))
			{
				params.add<Params::r_float>(name.toStdString(),
											from_str<Params::r_float>(value_from.toStdString()),
											from_str<Params::r_float>(value_to.toStdString()),
											from_str<Params::r_float>(step.toStdString()));
			}
			else
			{
				params.add<Params::r_int>(name.toStdString(),
										  from_str<Params::r_int>(value_from.toStdString()),
										  from_str<Params::r_int>(value_to.toStdString()),
										  from_str<Params::r_int>(step.toStdString()));
			}
		}
		else if (cmd.compare("get") == 0)
		{
			send_to_client(client, params.get_str(name.toStdString()));
		}

		//params.add<unsigned long int>(name.toStdString())
	}

	void PAT_Server::new_connection()
	{
		qDebug() << "conn";
		QTcpSocket * client = this->nextPendingConnection();
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}

}
