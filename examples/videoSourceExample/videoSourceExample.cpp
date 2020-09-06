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
    "/", HttpServerCallback(socket, request) {
      CpqVideoCapture* source = new CpqVideoCapture;
      QThread* thr = new QThread;

      HttpReplaceClientHandler* handler =
        new HttpReplaceClientHandler("image/jpeg");
      auto* controller = new HandlerController(handler, socket);

      QObject::connect(
        socket, &QObject::destroyed, []() { qDebug() << " - socket(("; });

      QObject::connect(thr, &QThread::started, [=]() {
        bool ok = false;

        if (request.route == "/") {
          ok = source->capture(0);
        } else {
          // request.route.right(request.route.length() - 1);
          ok = source->capture("http://123localhost/asd");
        }
        if (ok) {
          QObject::connect(
            controller, &QObject::destroyed, source, &QObject::deleteLater);
          QObject::connect(source,
                           &CpqVideoCapture::jpegCaptured,
                           handler,
                           &HttpReplaceClientHandler::updateData);
          QObject::connect(thr, &QThread::finished, thr, &QThread::deleteLater);

          handler->start();
        }
      });

      thr->start();

      // QObject::connect(source,
      //                 &CpqVideoCapture::frameCaptured,
      //                 [=](cpq::vis::CpqMat mat) -> void {
      //                   qDebug() << handler;
      //                   handler->updateData(mat2Jpeg(mat));
      //                 });
    });

  return a.exec();
}
