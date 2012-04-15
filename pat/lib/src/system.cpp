
#include "pat/system.hpp"

namespace pat
{
    System::System() : host("127.0.0.1"), port(13314), socket(new QTcpSocket), block_size(0)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

    System::System(const std::string & host, unsigned int port):
		host(host), port(port), socket(new QTcpSocket), block_size(0)
	{
		socket->connectToHost(QHostAddress(QString::fromUtf8(host.c_str())), port);
	}

    System::~System()
	{
		socket->disconnect();
		delete socket;
	}

    void System::send_message_to_server(std::string cmd, std::string res)
	{
		QByteArray arr_block;
		QDataStream out(&arr_block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

        out << quint32(0) << QString(cmd.c_str()) << QString(res.c_str());
		out.device()->seek(0);
		out << quint32(arr_block.size() - sizeof(quint32));

		socket->write(arr_block);

		socket->waitForBytesWritten();
	}

    void System::send_result(double result)
	{
        send_message_to_server("result", to_str(result, 0, 32));
	}
}
