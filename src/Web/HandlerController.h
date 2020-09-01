#ifndef HANDLERCONTROLLER_H
#define HANDLERCONTROLLER_H

#include "ClientHandlers/AbstractClientHandler.h"
#include <QObject>
#include <QTcpSocket>

namespace cpq {
namespace web {

class HandlerController : public QObject
{
  Q_OBJECT
public:
  explicit HandlerController(AbstractClientHandler* handler,
                             QTcpSocket* socket,
                             QObject* parent = nullptr);
  ~HandlerController();

  static void obtain(AbstractClientHandler* handler, QTcpSocket* socket);

public slots:
  void readFromSocket();
  void readFromHandler(const QByteArray& bytes);
  void onSocketClosed();
  void closeSocket();

signals:
  void writeToHandler(const QByteArray& bytes);
  void socketClosed();

private:
  AbstractClientHandler* handler;
  QTcpSocket* socket;
};

}
}

#endif // HANDLERCONTROLLER_H
