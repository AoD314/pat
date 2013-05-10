
#include "server.hpp"

namespace pat
{
	Server::Server(Settings settings)
	{
		block_size = 0;
		count_connection = 0;

		if (!this->listen(QHostAddress::Any, settings.port()))
		{
			throw QString("Unable to start the server : " + this->errorString());
		}

		connect(this, SIGNAL(newConnection()), this, SLOT(new_connection()));
		emit log(QString("start server on port: " + QString::number(settings.port())));
	}

	void Server::read()
	{
		emit log(QString("sender() = ") + QString(sender()->staticMetaObject.className()));

		QTcpSocket * client = (QTcpSocket *)sender();

		last_client = client;
		QDataStream in(last_client);
		in.setVersion(QDataStream::Qt_4_7);

		QString cmd;

		for (;;)
		{
			emit log(QString("block size = ") +QString::number(block_size));
			emit log(QString("client = ") + QString::number((size_t)last_client, 16));
			emit log(QString("client->bytesAvailable() = ") + QString::number(last_client->bytesAvailable()));

			if (!block_size)
			{
				if (static_cast<size_t>(last_client->bytesAvailable()) < sizeof(quint32))
				{
					break;
				}
				in >> block_size;
				emit log(QString("block size = ") +QString::number(block_size) + QString("     client->bytesAvailable() = ") + QString::number(client->bytesAvailable()));
			}

			if (last_client->bytesAvailable() < block_size)
			{
				break;
			}

			in >> cmd;

			block_size = 0;

			if (cmd.compare("init") == 0)
			{
				QString name, type, size_s;
				in >> name;
				in >> type;
				in >> size_s;

				size_t size = from_str<size_t>(size_s.toStdString());
				Number value;

				std::vector<Number> list;
				for (size_t i = 0; i < size; ++i)
				{
					in >> value;
					list.push_back(value);
				}

				emit log(QString("read command : init " + name + " type:" + type + " size:" + size_s));

				if (type.compare("ab") == 0)
				{
					emit init(name, Gen(list.at(0), list.at(1)));
				}
				else if (type.compare("abs") == 0)
				{
					emit init(name, Gen(list.at(0), list.at(1), list.at(2)));
				}
				else if (type.compare("vec") == 0)
				{
					emit init(name, Gen(list));
				}

			}
			else if (cmd.compare("get") == 0)
			{
				QString name;
				in >> name;

				emit log(QString("read command : get " + name));
				emit get(name);
			}
			else if (cmd.compare("alg") == 0)
			{
				QString name;
				in >> name;

				emit log(QString("read command : alg " + name));
				emit alg(name);
			}
			else if (cmd.compare("params") == 0)
			{
				QString name;
				QString value;
				in >> name;
				in >> value;

				emit log(QString("read params : " + name + " = " + value));
				emit params(name, value);
			}
			else if (cmd.compare("result") == 0)
			{
				QString value;
				in >> value;

				emit log(QString("read command : result " + value));
				emit result(from_str<double>(value.toStdString()));
			}
		}
	}

	void Server::send_value_to_client(QTcpSocket * socket, QString value)
	{
		emit log(QString("send value(" + value + ") to client"));
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		out << quint32(0) << value;
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

	void Server::send_to_client(QString value)
	{
		emit log(QString("send to client : " + value));
		send_value_to_client(last_client, value);
	}

	void Server::new_connection()
	{
		count_connection++;
		emit log("\n ===================================================== \n");
		emit log("new connection : " + QString::number(count_connection));
		QTcpSocket * client = this->nextPendingConnection();
		emit log(QString("new client = ") + QString::number((size_t)client, 16));
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}
}
