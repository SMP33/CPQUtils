#include "HandlerController.h"

using namespace cpq::web;

HandlerController::HandlerController(AbstractClientHandler* handler,
                                     QTcpSocket* socket,
                                     QObject* parent)
  : QObject(parent)
  , handler(handler)
  , socket(socket)
{
  connect(
    socket, &QTcpSocket::readyRead, this, &HandlerController::readFromSocket);

  connect(handler,
          &AbstractClientHandler::write,
          this,
          &HandlerController::readFromHandler);

  connect(handler,
          &AbstractClientHandler::closeSocket,
          this,
          &HandlerController::closeSocket);

  connect(socket,
          &QTcpSocket::disconnected,
          handler,
          &AbstractClientHandler::socketClosed);

  connect(handler, &QObject::destroyed, this, &QObject::deleteLater);
}

cpq::web::HandlerController::~HandlerController() {

  handler = nullptr;
}

void
HandlerController::obtain(AbstractClientHandler* handler, QTcpSocket* socket)
{
  new HandlerController(handler, socket);
}

void
HandlerController::readFromSocket()
{}

void
HandlerController::readFromHandler(const QByteArray& bytes)
{
  if (socket != nullptr) {
    if (socket->isWritable()) {
      socket->write(bytes);
      socket->flush();
    }
  }
}

void
HandlerController::onSocketClosed()
{}

void
HandlerController::closeSocket()
{
  socket->flush();
  socket->close();
}
