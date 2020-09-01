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

CpqVideoCaptureWorker_private::~CpqVideoCaptureWorker_private()
{
  capture.release();
}

void
CpqVideoCaptureWorker_private::run()
{
  Mat mat;

  while (true) {
    this->usleep(1e5);

    if (capture.read(mat)) {
      CpqMat m(mat);

      emit frameCaptured(m);
    }
  }
}

#endif
