#include "HttpReplaceClientHandler.h"
#include <QDebug>
#include <QThread>

HttpReplaceClientHandler::HttpReplaceClientHandler(QString title,
                                                   QObject* parent)
  : AbstractClientHandler(parent)
  , title(title)
  , isStarted(false)
  , mutex(QMutex::NonRecursive)
{}

void
HttpReplaceClientHandler::read(const QByteArray& bytes)
{
  qDebug() << bytes;
}

void
HttpReplaceClientHandler::socketClosed()
{
  mutex.lock();
  isStarted = false;
  mutex.unlock();

  emit disconnected();
  qDebug() << "closed";
  deleteLater();
}

void
HttpReplaceClientHandler::updateData(QByteArray data)
{
  qDebug() << "Before mutex";
  //  mutex.lock();
  bool upd = isStarted;
  //  mutex.unlock();
  qDebug() << "After mutex";

  if (upd) {
    QByteArray boundary = ("--boundary\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: ");

    boundary.append(QString::number(data.length()));
    boundary.append("\r\n\r\n");
    boundary.append(data);
    //  emit write(boundary);
    emit write(data);
  }

  qDebug() << data;
}

void
HttpReplaceClientHandler::start()
{
  //  QByteArray header =
  //    ("HTTP/1.0 200 OK\r\n"
  //     "Server: en.code-bude.net example server\r\n"
  //     "Cache-Control: no-cache\r\n"
  //     "Cache-Control: private\r\n"
  //     "Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n");

  QByteArray header = ("HTTP/1.0 200 OK\r\n\r\n\r\n123");

  emit write(header);
  //  emit closeSocket();

  mutex.lock();
  isStarted = true;
  mutex.unlock();

  qDebug() << "Started";
}
