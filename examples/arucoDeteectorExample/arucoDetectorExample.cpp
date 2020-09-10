#include <QCoreApplication>
#include <QDebug>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>

#include "../../src/Vision.h"
#include "../../src/Web.h"

#include <Eigen/Core>

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cpq;
using namespace cpq::web;
using namespace cpq::vis;

int
main(int argc, char* argv[])
{
  Eigen::Quaterniond q(Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX()) *
                       Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY()) *
                       Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ()));

  QCoreApplication a(argc, argv);

  ArucoMarkerMap map = loadArucoMap(":/aruco_map.txt");
  Mat mapMat;
  std::shared_ptr<cv::aruco::Dictionary> dict =
    cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_1000);

  cv::Ptr<cv::aruco::Board> board;
  arucoMapToBoard(map, board, dict);
  // drawArucoMarkerMap(10, mapMat, map, dict);
  cv::aruco::drawPlanarBoard(board, cv::Size(600, 900), mapMat);
  QByteArray jpegMap = mat2Jpeg(mapMat);

  cv::Mat camera_matrix = (cv::Mat1f(3, 3) << 308.1207554696,
                           0.0000000000,
                           303.5824891638,
                           0.0000000000,
                           307.9848046436,
                           244.3864185646,
                           0.0000000000,
                           0.0000000000,
                           1.0000000000);
  cv::Mat distorsion_array = (cv::Mat1f(5, 1) << -0.3081371493,
                              0.1013386430,
                              -0.0000344732,
                              -0.0001545724,
                              -0.0155932033);

  ArucoDetector::DetectorSettings settings(
    board, &camera_matrix, &distorsion_array);

  // settings.board = board;
  // settings.camera_matrix = std::shared_ptr<cv::Mat>(new Mat(camera_matrix));
  // settings.distorsion_array =
  //  std::shared_ptr<cv::Mat>(new Mat(distorsion_array));

  HttpServer server;
  server.listen(QHostAddress::Any, 8080);

  QMap<QString, QString> mapHeaders;
  mapHeaders["Content-Type"] = "image/jpeg";
  mapHeaders["Content-Length"] = QByteArray::number(jpegMap.length());

  server.addRouteResponse("/map", HttpResponse(jpegMap, 200, "OK", mapHeaders));

  server.addRouteCallback(
    "/", [settings](QTcpSocket* socket, cpq::web::HttpRequest request) {
      ArucoDetector* source = new ArucoDetector;
      source->setSettings(settings);

      QThread* thr = new QThread;

      HttpReplaceClientHandler* handler =
        new HttpReplaceClientHandler("image/jpeg");
      auto* controller = new HandlerController(handler, socket);

      QObject::connect(thr, &QThread::started, [=]() {
        bool ok = false;

        if (request.route == "/") {
          ok = source->capture(0);
        } else {
          // request.route.right(request.route.length() - 1);
          ok = source->capture("http://123localhost/asd");
        }
        if (ok) {
          source->set(cv::CAP_PROP_FPS, 30);
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
