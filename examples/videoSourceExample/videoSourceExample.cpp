#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include <opencv2/opencv.hpp>

using namespace cv;

//#include "../../src/Vision.h"
//#include "../../src/Web.h"

// using namespace cpq;
// using namespace cpq::vis;

int
main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  Mat mat;

  auto capture = VideoCapture(0);

  while (true) {
    QThread::sleep(1);

    capture >> mat;
    imshow("Video", mat);
  }

  //  CpqVideoCapture source;
  //  source.capture(0);

  return a.exec();
}
