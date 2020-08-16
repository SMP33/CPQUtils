#include "../Web.h"
#include <QCoreApplication>
#include <QDebug>

using namespace CPQ::Web;

int
main(int argc, char* argv[])
{
  qDebug() << "Start simpleHttpServer example";
  QCoreApplication a(argc, argv);

  HTTPServer server(8080);

  server.addRouteResponse("/", [](HTTPRequest request) -> HTTPResponse {
    return HTTPResponse("Hello dear " + request.headers["User-Agent"]);
  });

  server.set404Responce([](HTTPRequest request) -> HTTPResponse {
    return HTTPResponse("What is " + request.route + "?");
  });

  server.start();

  return a.exec();
}
