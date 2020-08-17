#include "../Web.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

using namespace CPQ::Web;

int
main(int argc, char* argv[])
{
  qDebug() << "Start simpleHttpServer example";
  QCoreApplication a(argc, argv);

  HttpServer server(8080);

  server.addRouteResponse("/", [](HTTPRequest request) -> HTTPResponse {
    return HTTPResponse("Hello dear " + request.headers["User-Agent"]);
  });

  server.set404Responce([](HTTPRequest request) -> HTTPResponse {
    return HTTPResponse("What is " + request.route + "?");
  });

  server.addRouteCallback(
    "/count", [](QTcpSocket* socket, HTTPRequest) -> void {
      HttpReplaceClientHandler* handler = new HttpReplaceClientHandler();
      new HandlerController(handler, socket);

      QTimer* timer = new QTimer();
      QObject::connect(timer, &QTimer::timeout, [&]() {
        QByteArray data = "Check";
        qDebug() << data;
        handler->updateData("asd");
      });

      QObject::connect(handler, &AbstractClientHandler::disconnected, [&]() {
        qDebug() << "DISCONNECTED!";
        timer->stop();
        timer->deleteLater();
      });

      handler->start();
      timer->start(1e3);
    });

  server.start();
  return a.exec();
}
