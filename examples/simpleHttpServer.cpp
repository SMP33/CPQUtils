#include "../src/Web.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

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

  server.addRouteResponse("/", [](HttpRequest) -> HttpResponse {
    QByteArray data = "<html>"
                      "<head>\r\n"
                      "    <style type=\"text/css\">\r\n"
                      "        body {\r\n"
                      "            display: table;\r\n"
                      "            margin: auto;\r\n"
                      "        }\r\n"
                      "    </style>\r\n"
                      "</head>\r\n"
                      "\r\n"
                      "<body>\r\n"
                      "<h1>This is example page!</h1>"
                      "<a href=\"hello\">HTTP header example</a>"
                      "<br>"
                      "<a href=\"count\">multipart/x-mixed-replace example</a>"
                      "</body>\r\n"
                      "</html>";

    return HttpResponse(data);
  });

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
        qDebug() << "DISCONNECTED!";
        timer->stop();
        timer->deleteLater();
        delete count;
      });

      handler->start();
      timer->start(1e2);
    });

  return a.exec();
}
