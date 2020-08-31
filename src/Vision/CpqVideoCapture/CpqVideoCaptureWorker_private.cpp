#ifndef NO_OPENCV

#include "CpqVideoCaptureWorker_private.h"

using namespace cpq::vis;
using namespace cv;

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(int index,
                                                             QObject* parent)
{
  capture = VideoCapture(index);
}

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(QString file,
                                                             QObject* parent)
{}

void
CpqVideoCaptureWorker_private::run()
{
  Mat mat;

  while (true) {
    this->usleep(1e5);

    capture >> mat;
    emit frameCaptured(mat);
  }
}

#endif
