
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
	}

	void Server::read()
	{
		QTcpSocket * client = (QTcpSocket *)sender();
		
		last_client = client;
		QDataStream in(last_client);
		in.setVersion(QDataStream::Qt_4_7);

		int super_counter = 0;

		while(true) {
			super_counter++;
			qDebug() << "client.iter #" << super_counter << ":" << last_client;

		QString cmd;

		if (!block_size)
		{
			if (!last_client->isValid())
			{
				break;
			}

			emit log("try get bytesAvailable() #1");
			size_t ba = last_client->bytesAvailable();
			emit log("bytesAvailable() = " + to_str(ba));

			if (ba < sizeof(quint32))
			{
				break;
				//return;
			}
			in >> block_size;
			emit log("block_size=" + to_str(block_size));
		}

		emit log("try get bytesAvailable() #2");
		size_t ba = last_client->bytesAvailable();
		emit log("bytesAvailable() = " + to_str(ba));
		if (ba < block_size)
		{
			break;
			//return;
		}

		in >> cmd;

		emit log(std::string(cmd.toAscii()));

		block_size = 0;
		qDebug() << "block_size=0; last_client:" << last_client;

		if (cmd.compare("init") == 0)
		{
			QString qname, qtype, qsize_s;
			in >> qname;
			in >> qtype;
			in >> qsize_s;

			std::string name = qname.toAscii();
			std::string type = qtype.toAscii();
			std::string size_s = qsize_s.toAscii();

			size_t size = from_str<size_t>(size_s);
			Number value;

			std::vector<Number> list;
			for (size_t i = 0; i < size; ++i)
			{
				in >> value;
				list.push_back(value);
			}

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
			QString qname;
			in >> qname;
			std::string name = qname.toAscii();

			emit get(name);
		}
		else if (cmd.compare("alg") == 0)
		{
			QString qname;
			in >> qname;

			std::string name(qname.toAscii());

			emit alg(name);
		}
		else if (cmd.compare("params") == 0)
		{
			QString qname, qvalue;
			in >> qname;
			in >> qvalue;

			std::string name(qname.toAscii());
			std::string value(qvalue.toAscii());

			emit params(name, value);
		}
		else if (cmd.compare("result") == 0)
		{
			QString qvalue;
			in >> qvalue;

			std::string value(qvalue.toAscii());

			emit result(from_str<double>(value));

			break;
		}
		qDebug() << "end of while() #" << last_client;
		} // while
		//qDebug() << "end of     READ       ===========================> #" << last_client;
	}

	void Server::send_value_to_client(QTcpSocket * socket, std::string value)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		//emit log("send to client: " + value);

		out << quint32(0) << QString::fromStdString(value);
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

	void Server::send_to_client(std::string value)
	{
		send_value_to_client(last_client, value);
	}

	void Server::new_connection()
	{
		count_connection++;
		QTcpSocket * client = this->nextPendingConnection();
		connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
		connect(client, SIGNAL(readyRead()),    this,   SLOT(read()));
	}
}
