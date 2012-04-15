
#include <QDebug>

#include "pat/application.hpp"

namespace pat
{

    Application::Application(int argc, char ** argv) : settings(argc, argv), server(settings)
    {
        connect(&server, SIGNAL(log(QString)), this, SLOT(print_log(QString)));
    }

    void Application::print_log(QString msg)
    {
        msg = QTime::currentTime().toString("hh:mm:ss.zzz") + "     :   " + msg;
        qDebug() << msg;
    }


}
