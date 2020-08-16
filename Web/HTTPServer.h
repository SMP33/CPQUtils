#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QRegularExpression>
#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>

namespace CPQ {

namespace Web {

struct HTTPRequest
{
  HTTPRequest(QByteArray request);

  QString method;
  QString route;
  QString protocol;
  QMap<QString, QString> headers;
  QByteArray body;
};

struct HTTPResponse
{
  explicit HTTPResponse(
    const QByteArray& body,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  explicit HTTPResponse(
    const QString& body,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  QByteArray toQByteArray();

  QByteArray body;
  qint16 statusCode = 200;
  QString reasonPhrase = "OK";
  QMap<QString, QString> headers;
  QString version = "HTTP/1.1";
};

class HTTPServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit HTTPServer(quint16 port = 8080, QObject* parent = nullptr);

  void addRouteCallback(QString route,
                        std::function<void(QTcpSocket*, HTTPRequest)> functor);
  void addRouteResponse(QString route,
                        std::function<HTTPResponse(HTTPRequest)> functor);
  void set404Callback(std::function<void(QTcpSocket*, HTTPRequest)> functor);
  void set404Responce(std::function<HTTPResponse(HTTPRequest)> functor);

  template<typename Functor>
  void addRouteCallback(QString route, Functor functor);
  template<typename Functor>
  void addRouteResponse(QString route, Functor functor);
  template<typename Functor>
  void set404Callback(Functor functor);
  template<typename Functor>
  void set404Responce(Functor functor);

public slots:
  void start();
  void newConnection();
  void firstReadClient();

private:
  quint16 port;
  QMutex* mutex;

  QMap<QString, std::function<void(QTcpSocket*, HTTPRequest)>> callbackMap;
  std::function<void(QTcpSocket*, HTTPRequest)> handler404;
};

template<typename Functor>
void
HTTPServer::addRouteCallback(QString route, Functor functor)
{
  // QMutexLocker locker(mutex);
  callbackMap.insert(route, [functor](QTcpSocket* socket, HTTPRequest request) {
    functor(socket, request);
  });
}

template<typename Functor>
void
HTTPServer::addRouteResponse(QString route, Functor functor)
{
  auto functor_ = [functor](QTcpSocket* socket, HTTPRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };

  this->addRouteCallback(route, functor_);
}

template<typename Functor>
void
HTTPServer::set404Callback(Functor functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HTTPRequest request) {
    functor(socket, request);
  };
}

template<typename Functor>
void
HTTPServer::set404Responce(Functor functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HTTPRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };
}
} // namespace Web
} // namespace CPQ

#endif // HTTPSERVER_H
