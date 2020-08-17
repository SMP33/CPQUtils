#include "HttpServer.h"
using namespace CPQ::Web;

HttpServer::HttpServer(quint16 port, QObject* parent)
  : QTcpServer(parent)
  , port(port)
  , mutex(new QMutex())
{
  setMaxPendingConnections(10);

  set404Responce([](HTTPRequest request) -> HTTPResponse {
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

    return HTTPResponse(arr);
  });
}

void
HttpServer::addRouteCallback(QString route,
                             std::function<void(QTcpSocket*, HTTPRequest)> func)
{
  callbackMap.insert(route, func);
}

void
HttpServer::addRouteResponse(QString route,
                             std::function<HTTPResponse(HTTPRequest)> functor)
{
  auto functor_ = [functor](QTcpSocket* socket, HTTPRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };

  this->addRouteCallback(route, functor_);
}

void
HttpServer::set404Callback(std::function<void(QTcpSocket*, HTTPRequest)> func)
{
  QMutexLocker locker(mutex);
  handler404 = func;
}

void
HttpServer::set404Responce(std::function<HTTPResponse(HTTPRequest)> functor)
{
  QMutexLocker locker(mutex);
  handler404 = [functor](QTcpSocket* socket, HTTPRequest request) -> void {
    socket->write(functor(request).toQByteArray());
    socket->flush();
    socket->close();
  };
}

void
HttpServer::start()
{
  assert(this->listen(QHostAddress::Any, port));

  connect(this, &QTcpServer::newConnection, this, &HttpServer::newConnection);
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

  HTTPRequest request(buf);
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

HTTPRequest::HTTPRequest(QByteArray request)
{
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

HTTPResponse::HTTPResponse(const QByteArray& body,
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

HTTPResponse::HTTPResponse(const QString& body,
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

QByteArray
HTTPResponse::toQByteArray()
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
