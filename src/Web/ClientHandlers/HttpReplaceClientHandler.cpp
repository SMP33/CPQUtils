#include "HttpReplaceClientHandler.h"
#include <QDebug>
#include <QThread>

using namespace cpq::web;

HttpReplaceClientHandler::HttpReplaceClientHandler(QByteArray contentType,
                                                   QByteArray boundary,
                                                   QObject* parent)
  : AbstractClientHandler(parent)
  , contentType(contentType)
  , boundary(boundary)
  , isStarted(false)
  , closedBeforeStart(false)
  , mutex(new QMutex)
{}

void
HttpReplaceClientHandler::read(const QByteArray&)
{
  QMutexLocker locker(mutex);
}

void
HttpReplaceClientHandler::socketClosed()
{
  QMutexLocker locker(mutex);
  if (!isStarted) {
    closedBeforeStart = true;
  } else {
    isStarted = false;
    emit disconnected();
    deleteLater();
  }
}

void
HttpReplaceClientHandler::updateData(QByteArray data)
{
  QMutexLocker locker(mutex);

  if (isStarted) {
    QByteArray subHeader = boundary +
                           "\r\n"
                           "Content-Type: " +
                           contentType +
                           "\r\n"
                           "Content-Length: ";

    subHeader.append(QByteArray::number(data.length()));
    subHeader.append("\r\n\r\n");
    subHeader.append(data);

    emit write(subHeader);
  }
}

void
HttpReplaceClientHandler::start()
{

  QMutexLocker locker(mutex);
  isStarted = true;

  if (closedBeforeStart) {
    emit started();
    emit disconnected();
    deleteLater();
  } else {
    QByteArray header =
      "HTTP/1.0 200 OK\r\n"
      //                      "Server: en.code-bude.net example server\r\n"
      //    "Cache-Control: no-cache\r\n"
      //    "Cache-Control: private\r\n"
      "Content-Type: multipart/x-mixed-replace;boundary=" +
      boundary + "\r\n\r\n";

    emit write(header);
    emit started();
  }

  
}
