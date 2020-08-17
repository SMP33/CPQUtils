#ifndef HttpReplaceClientHandler_H
#define HttpReplaceClientHandler_H

#include "AbstractClientHandler.h"
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QString>

class HttpReplaceClientHandler : public AbstractClientHandler
{
  Q_OBJECT
public:
  HttpReplaceClientHandler(QString contentType = "text/html",
                           QObject* parent = nullptr);

  // AbstractClientHandler interface
public slots:
  void read(const QByteArray& bytes);
  void socketClosed();
  void updateData(QByteArray data);
  void start();

private:
  QString title;
  bool isStarted;
  QMutex mutex;
};

#endif // HttpReplaceClientHandler_H
