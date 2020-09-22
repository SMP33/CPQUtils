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
  QCoreApplication a(argc, argv);

  return a.exec();
}
