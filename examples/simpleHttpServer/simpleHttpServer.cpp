#define INCBIN_PREFIX

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "../../src/Web.h"

using namespace cpq::web;

QString operator"" _qStr(const char* str, size_t size)
{
  return QString(str);
}

QByteArray operator"" _qba(const char* str, size_t size)
{
  return QByteArray(str);
}

int
main(int argc, char* argv[])
{

  qDebug() << "Start simpleHttpServer example"_qStr;

  QCoreApplication a(argc, argv);
  HttpServer server;

  server.listen(QHostAddress::Any, 8080);

  server.addRouteResponse("/", HttpResponse::fromFile(":/index.html"));

  server.addRouteResponse("/simplest", "Hello world!");

  server.addRouteResponse("/hello", [](HttpRequest request) -> HttpResponse {
    QByteArray data = "Hello dear " + request.headers["User-Agent"].toUtf8();
    return HttpResponse(data);
  });

  server.set404Responce([](HttpRequest request) -> HttpResponse {
    return HttpResponse("What is " + request.route + "?");
  });

  server.addRouteCallback(
    "/count", [](QTcpSocket* socket, HttpRequest) -> void {
      HttpReplaceClientHandler* handler = new HttpReplaceClientHandler();
      new HandlerController(handler, socket);

      int* count = new int(0);

      QTimer* timer = new QTimer();
      QObject::connect(timer, &QTimer::timeout, [=]() {
        QByteArray data = "<b>" + QByteArray::number(float(*count) / 10) +
                          "</b> seconds passed";

        (*count)++;
        handler->updateData(data);
      });

      QObject::connect(handler, &AbstractClientHandler::disconnected, [=]() {
        timer->stop();
        timer->deleteLater();
        delete count;
      });

      handler->start();
      timer->start(1e2);
    });

  return a.exec();
}
