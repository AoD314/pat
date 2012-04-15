
#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <QtCore>

#include "patconfig.hpp"
#include "pat/settings.hpp"
#include "pat/server.hpp"

namespace pat
{
    class PAT_EXPORTS Application : public QObject
    {
        Q_OBJECT

        private:
            Settings settings;
            Server server;

        public:
            Application(int argc, char ** argv);

        public slots:
            void print_log(QString msg);
    };

}


#endif

