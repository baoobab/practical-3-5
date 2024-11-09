#include "application.h"
#include "common.h"


TApplication::TApplication(int argc, char *argv[])
            : QApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,
                         QHostAddress("127.0.0.1"), 10000};
    comm = new TCommunicator(pars, this);

    interface = new TInterface();
    interface->show();

    connect(comm,SIGNAL(recieved(QJsonDocument)),this,
            SLOT(fromCommunicator(QJsonDocument)));
    connect(interface,SIGNAL(request(QJsonDocument)),
            this,SLOT(toCommunicator(QJsonDocument)));

}

void TApplication::fromCommunicator(QJsonDocument jsonDoc)
{
    interface->answer(jsonDoc);
}

void TApplication::toCommunicator(QJsonDocument jsonDoc)
{
    comm->send(jsonDoc);
}
