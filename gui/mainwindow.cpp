
#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
{
	QTextEdit    * edit   = new QTextEdit("full path to testsystem application");
	QPushButton  * button = new QPushButton("RUN");
	QTextBrowser * text   = new QTextBrowser;

	QHBoxLayout * layout_h = new QHBoxLayout;
	layout_h->addWidget(edit);
	layout_h->addWidget(button);

	QVBoxLayout * layout_v = new QVBoxLayout;
	layout_v->addLayout(layout_h);
	layout_v->addWidget(text);

	setLayout(layout_v);

	port = 13314;
	server = new QTcpServer;
	if (!server->listen(QHostAddress::Any, port))
	{
		QMessageBox::critical(0, "Server Error", "Unable to start the server : " + server->errorString());
		server->close();
		return;
	}

	connect(server, SIGNAL(newConnection()), this, SLOT(new_connection()));

}

void MainWindow::send_to_client(QTcpSocket * socket, std::string value)
{
	QByteArray arr_block;
	QDataStream out(&arr_block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);


	out << quint32(0) << QString(value.c_str());
	out.device()->seek(0);
	out << quint32(arr_block.size() - sizeof(quint32));

	socket->write(arr_block);
}

void MainWindow::read_client()
{
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

	quint32 block_size = 0;

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

		block_size = 0;

		if (q_cmd.compare("get") == 0)
		{
			send_to_client(client, "1111");
		}
	}
}

void MainWindow::new_connection()
{
	QTcpSocket * client = server->nextPendingConnection();

	connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
	connect(client, SIGNAL(readyRead()), this, SLOT(read_client()));
}
