#ifndef NO_OPENCV

#include "CpqVideoCaptureWorker_private.h"

using namespace cpq::vis;
using namespace cv;

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(QString camera)
  : QThread(nullptr)
{
  bool isInt=false;
  camera.toInt(&isInt);

  if (isInt) {
    capture = VideoCapture(camera.toInt(),CAP_DSHOW);
  } else {
    capture = VideoCapture(camera.toStdString());
  }

  m_isOpened = capture.isOpened();

  if (m_isOpened) {
    start();
  }
}

void
cpq::vis::CpqVideoCaptureWorker_private::release()
{
  qDebug() << 2 << QThread::currentThread();
  m_continueRun = false;
}

bool
cpq::vis::CpqVideoCaptureWorker_private::isOpened() const
{
  return false;
}

CpqVideoCaptureWorker_private::~CpqVideoCaptureWorker_private()
{
}

void
CpqVideoCaptureWorker_private::run()
{
  Mat mat;

  while (continueRun()) {
    this->usleep(1e5);

    if (capture.read(mat)) {
      CpqMat m(mat);

      emit frameCaptured(m);
      emit jpegCaptured(mat2Jpeg(m));
    }

  }
  qDebug() <<3<< QThread::currentThread();
  //capture.release();
  qDebug() << capture.isOpened();

  deleteLater();
}

bool
cpq::vis::CpqVideoCaptureWorker_private::continueRun() const
{
  return m_continueRun;
}

#endif
