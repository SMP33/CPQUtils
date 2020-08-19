#ifndef HttpReplaceClientHandler_H
#define HttpReplaceClientHandler_H

#include "AbstractClientHandler.h"
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QString>

namespace cpq {

namespace web {

class HttpReplaceClientHandler : public AbstractClientHandler
{
  Q_OBJECT
public:
  HttpReplaceClientHandler(QByteArray contentType = "text/html",
                           QByteArray boundary = "--boundary",
                           QObject* parent = nullptr);

  // AbstractClientHandler interface
public slots:
  void read(const QByteArray& bytes);
  void socketClosed();
  void updateData(QByteArray data);
  void start();

private:
  QByteArray contentType;
  QByteArray boundary;
  bool isStarted;
  QMutex* mutex;
};

}

}

#endif // HttpReplaceClientHandler_H
