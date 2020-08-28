#include "HttpServer.h"

using namespace cpq::web;

HttpServer::HttpServer(QObject* parent)
  : QTcpServer(parent)
  , mutex(new QMutex())
{
  connect(this, &QTcpServer::newConnection, this, &HttpServer::newConnection);
  setMaxPendingConnections(10);

  set404Responce([](HttpRequest request) -> HttpResponse {
    QByteArray arr = "<html>\r\n"
                     "<head>"
                     "<title>404</title>"
                     "<style>"
                     ".text {"
                     "text-align:  center;"
                     "}"
                     "</style>"
                     "</head>"
                     "<body>"
                     "<div class=\"text\">"
                     "<h1>404!</h1>"
                     "Could not find page <b>" +
                     request.route.toUtf8() +
                     "</b>"
                     "</div>"
                     "</body>"
                     "</html>";

    return HttpResponse(arr);
  });
}

void
HttpServer::addRouteCallback(QString route,
                             std::function<void(QTcpSocket*, HttpRequest)> func)
{
  callbackMap.insert(route, func);
}

void
HttpServer::addRouteResponse(QString route,
                             std::function<HttpResponse(HttpRequest)> functor)
{
  auto functor_ = [functor](QTcpSocket* socket, HttpRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };

  this->addRouteCallback(route, functor_);
}

void
HttpServer::addRouteResponse(QString route, HttpResponse response)
{
  addRouteResponse(route,
                   [=](HttpRequest) -> HttpResponse { return response; });
}

void
HttpServer::addRouteResponse(QString route,
                             QByteArray response,
                             qint16 statusCode,
                             const QString& reasonPhrase,
                             const QMap<QString, QString>& headers,
                             QString version)
{
  addRouteResponse(
    route, HttpResponse(response, statusCode, reasonPhrase, headers, version));
}

void
HttpServer::addRouteResponse(QString route,
                             QString response,
                             qint16 statusCode,
                             const QString& reasonPhrase,
                             const QMap<QString, QString>& headers,
                             QString version)
{
  addRouteResponse(
    route, HttpResponse(response, statusCode, reasonPhrase, headers, version));
}

void
HttpServer::addRouteResponse(QString route,
                             const char* response,
                             qint16 statusCode,
                             const QString& reasonPhrase,
                             const QMap<QString, QString>& headers,
                             QString version)
{
  addRouteResponse(
    route,
    HttpResponse(
      QByteArray(response), statusCode, reasonPhrase, headers, version));
}

void
HttpServer::set404Callback(std::function<void(QTcpSocket*, HttpRequest)> func)
{
  QMutexLocker locker(mutex);
  handler404 = func;
}

void
HttpServer::set404Responce(std::function<HttpResponse(HttpRequest)> functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HttpRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };
}

void
HttpServer::newConnection()
{
  QTcpSocket* socket = this->nextPendingConnection();

  connect(socket, &QTcpSocket::readyRead, this, &HttpServer::firstReadClient);
}

void
HttpServer::firstReadClient()
{
  QTcpSocket* socket = (QTcpSocket*)sender();
  QByteArray buf;

  while (socket->bytesAvailable() > 0) {
    buf.append(socket->readAll());
  }

  HttpRequest request(buf);
  QString route = request.route;
  bool matched = false;

  for (QString r : callbackMap.keys()) {
    QRegularExpressionMatch m = QRegularExpression("^" + r + "$").match(route);
    if (m.hasMatch()) {
      callbackMap[r](socket, request);
      matched = true;
      break;
    }
  }
  if (!matched) {
    handler404(socket, request);
  }
  disconnect(
    socket, &QTcpSocket::readyRead, this, &HttpServer::firstReadClient);
}

//
//Реализация методов структур
//

HttpRequest::HttpRequest(QByteArray request)
{
  /// QByteArray преобразуется в строку и парсится как строка.
  ///
  /// Заголовки отделяются от тела двумя идущими
  /// подряд символами  CRLF или LF.
  ///
  /// После нахождения разделителя данные
  /// преобразуются обратно в QByteArray.

  QString str = QString(request);
  QRegularExpression re("(\r\n|\n){2,}");
  auto match = re.match(str);
  if (!match.hasMatch())
    return;
  int end = match.capturedStart();

  QStringList lines;
  if (end != -1) {
    this->body = str.mid(end + match.captured(0).length()).toUtf8();
    lines = str.mid(0, end + 1).split('\n');
  } else {
    lines = str.split('\n');
  }

  if (lines.size() < 1)
    return;

  QStringList start = lines[0].split(" ");
  if (start.size() < 3)
    return;

  this->method = start[0].trimmed();
  this->route = start[1].trimmed();
  this->protocol = start[2].trimmed();

  lines.removeFirst();
  for (auto& line : lines) {
    line = line.trimmed();
    int sp = line.indexOf(":"); // splitter index
    if (sp > -1) {
      this->headers.insert(line.left(sp).trimmed(),
                           line.right(line.size() - sp - 1).trimmed());
    }
  }
}

HttpResponse::HttpResponse(const QByteArray& body,
                           qint16 statusCode,
                           const QString& reasonPhrase,
                           const QMap<QString, QString>& headers,
                           QString version)
  : body(body)
  , statusCode(statusCode)
  , reasonPhrase(reasonPhrase)
  , headers(headers)
  , version(version)

{}

HttpResponse::HttpResponse(const QString& body,
                           qint16 statusCode,
                           const QString& reasonPhrase,
                           const QMap<QString, QString>& headers,
                           QString version)
  : body(body.toUtf8())
  , statusCode(statusCode)
  , reasonPhrase(reasonPhrase)
  , headers(headers)
  , version(version)
{}

HttpResponse
HttpResponse::fromFile(QString path,
                       qint16 statusCode,
                       const QString& reasonPhrase,
                       const QMap<QString, QString>& headers,
                       QString version)
{
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray body = file.readAll();
    file.close();
    return HttpResponse(body, statusCode, reasonPhrase, headers, version);
  } else {
    return HttpResponse(
      QByteArray(""), statusCode, reasonPhrase, headers, version);
  }
}

QByteArray
HttpResponse::toQByteArray()
{
  QByteArray response;

  response = version.toUtf8() + " " + QString::number(statusCode).toUtf8() +
             " " + reasonPhrase.toUtf8() + "\r\n";

  for (const auto& header : headers) {
    response += header + ": " + headers[header] + "\r\n";
  }
  response += "\r\n";
  response += body;

  return response;
}
