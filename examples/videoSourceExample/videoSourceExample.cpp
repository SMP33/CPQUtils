#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "../../src/Vision.h"
#include "../../src/Web.h"

using namespace cpq;
using namespace cpq::web;
using namespace cpq::vis;

int
main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  QThread thr;

  HttpServer server;
  server.listen(QHostAddress::Any, 8080);

  server.addRouteCallback(
    "/", HttpServerCallback(socket, _) {
      CpqVideoCapture* source = new CpqVideoCapture;
      source->capture(0);

      HttpReplaceClientHandler* handler = new HttpReplaceClientHandler;

      new HandlerController(handler, socket);
      handler->start();
      QObject::connect(
        source,
        CpqVideoCapture::frameCaptured,
        [=](cpq::vis::CpqMat mat) -> void { handler->updateData(mat.data); });
    });

  return a.exec();
}
