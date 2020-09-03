#include <QCoreApplication>
#include <QDebug>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>

#include "../../src/Vision.h"
#include "../../src/Web.h"

#include <opencv2/opencv.hpp>

using namespace cpq;
using namespace cpq::web;
using namespace cpq::vis;

int
main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  qDebug() << "App started";

  HttpServer server;
  server.listen(QHostAddress::Any, 8080);

  server.addRouteCallback(
    "/", HttpServerCallback(socket, _) {

      HttpReplaceClientHandler* handler =
        new HttpReplaceClientHandler("image/jpeg");

            CpqVideoCapture* source = new CpqVideoCapture;
      source->capture(0);

      HandlerController::obtain(handler, socket);

      handler->start();

      QObject::connect(
        handler, &QObject::destroyed, source, &QObject::deleteLater);

      QObject::connect(source,
                       &CpqVideoCapture::jpegCaptured,
                       handler,
                       &HttpReplaceClientHandler::updateData);

      // QObject::connect(source,
      //                 &CpqVideoCapture::frameCaptured,
      //                 [=](cpq::vis::CpqMat mat) -> void {
      //                   qDebug() << handler;
      //                   handler->updateData(mat2Jpeg(mat));
      //                 });
    });

  return a.exec();
}
