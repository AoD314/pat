
#include "server.hpp"
#include "pat/pat_convert.hpp"
#include "pat/pat_strparam.hpp"

namespace pat
{
	PAT_Server::PAT_Server(int port) : QTcpServer(0)
	{
		block_size = 0;

		if (!this->listen(QHostAddress::Any, port))
		{
			QMessageBox::critical(0, "Server Error", "Unable to start the server : " + this->errorString());
			log(QString("Unable to start the server : " + this->errorString()));
			this->close();
			return;
		}

		connect(this, SIGNAL(newConnection()), this, SLOT(new_connection()));
	}

	void PAT_Server::change_state(Point p)
	{
	}

	void PAT_Server::send_value_to_client(QTcpSocket * socket, QString value)
	{
		log(QString("send to client : " + value));

		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0) << value;
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

		QString cmd;
		StrParams sp;

		for (;;)
		{
			if (!block_size)
			{
				if (static_cast<size_t>(client->bytesAvailable()) < sizeof(quint32))
				{
					break;
				}
				in >> block_size;
			}

			if (client->bytesAvailable() < block_size)
			{
				break;
			}

			in >> cmd;
			in >> sp.name;
			in >> sp.value_min;
			in >> sp.value_max;

			log(QString("server read: [command : " +  cmd + "] " + sp.to_str()));

			block_size = 0;

			// process

			if (cmd.compare("init") == 0)
			{
				init(sp);
			}
			else if (cmd.compare("get") == 0)
			{
				get(sp.name);
			}
			else if (cmd.compare("result") == 0)
			{
				result(from_str<double>(sp.name.toStdString()));
			}

		}
	}

	void PAT_Server::send_to_client(QString value)
	{
		send_value_to_client(last_client, value);
	}

	void PAT_Server::new_connection()
	{
		log("new connection");
		QTcpSocket * client = this->nextPendingConnection();
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}
}
