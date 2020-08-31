#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QRegularExpression>
#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>

#define HttpServerCallback(SOCKET_VAR, REQUEST_VAR)                            \
  [](QTcpSocket * SOCKET_VAR, cpq::web::HttpRequest REQUEST_VAR)

namespace cpq {

namespace web {

/// \brief Инкапсулирует HTTP запрос к серверу.
struct HttpRequest
{
  HttpRequest(QByteArray request);

  QString method;
  QString route;
  QString protocol;
  QMap<QString, QString> headers;
  QByteArray body;
};

/// \brief  Инкапсулирует ответ от сервера.
struct HttpResponse
{
  explicit HttpResponse(
    const QByteArray& body,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  explicit HttpResponse(
    const QString& body,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  static HttpResponse fromFile(
    QString path,
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

/// \brief HTTP сервер.
/// \details Простой HTTP сервер, наследуется от QTcpServer.
///  \todo Добавить доки.
class HttpServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit HttpServer(QObject* parent = nullptr);

  void addRouteCallback(QString route,
                        std::function<void(QTcpSocket*, HttpRequest)> functor);
  void addRouteResponse(QString route,
                        std::function<HttpResponse(HttpRequest)> functor);

  void addRouteResponse(QString route, HttpResponse response);
  void addRouteResponse(
    QString route,
    QByteArray response,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  void addRouteResponse(
    QString route,
    QString response,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  void addRouteResponse(
    QString route,
    const char* response,
    qint16 statusCode = 200,
    const QString& reasonPhrase = "OK",
    const QMap<QString, QString>& headers = QMap<QString, QString>(),
    QString version = "HTTP/1.1");

  void set404Callback(std::function<void(QTcpSocket*, HttpRequest)> functor);
  void set404Responce(std::function<HttpResponse(HttpRequest)> functor);

  template<typename Functor>
  void addRouteCallback(QString route, Functor functor);
  template<typename Functor>
  void addRouteResponse(QString route, Functor functor);
  template<typename Functor>
  void set404Callback(Functor functor);
  template<typename Functor>
  void set404Responce(Functor functor);

public slots:
  void newConnection();
  void firstReadClient();

private:
  QMutex* mutex;

  QMap<QString, std::function<void(QTcpSocket*, HttpRequest)>> callbackMap;
  std::function<void(QTcpSocket*, HttpRequest)> handler404;
};

template<typename Functor>
void
HttpServer::addRouteCallback(QString route, Functor functor)
{
  // QMutexLocker locker(mutex);
  callbackMap.insert(route, [functor](QTcpSocket* socket, HttpRequest request) {
    functor(socket, request);
  });
}

template<typename Functor>
void
HttpServer::addRouteResponse(QString route, Functor functor)
{
  auto functor_ = [functor](QTcpSocket* socket, HttpRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };

  this->addRouteCallback(route, functor_);
}

template<typename Functor>
void
HttpServer::set404Callback(Functor functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HttpRequest request) {
    functor(socket, request);
  };
}

template<typename Functor>
void
HttpServer::set404Responce(Functor functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HttpRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };
}
} // namespace Web
} // namespace CPQ

#endif // HTTPSERVER_H
