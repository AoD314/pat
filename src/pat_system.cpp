
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

	void PAT_System::send_result(double result)
	{

	}

	std::string PAT_System::get_params(const std::string & name)
	{
		return name;
	}
}
