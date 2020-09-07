#include "CpqVideoCapture.h"

using namespace cpq;
using namespace vis;

#ifndef NO_OPENCV

#include <opencv2/opencv.hpp>

#include "CpqVideoCaptureWorker_private.h"

#endif

#ifdef NO_OPENCV
CpqVideoCapture::CpqVideoCapture(QObject* parent)
  : QObject(parent){ NO_CV_WARNING() }

  cpq::vis::CpqVideoCapture::~CpqVideoCapture()
{}

bool
CpqVideoCapture::capture(int index)
{
  NO_CV_WARNING()
}

bool
CpqVideoCapture::capture(QString filename)
{
  NO_CV_WARNING()
}

#else
CpqVideoCapture::CpqVideoCapture(QObject* parent) {}

cpq::vis::CpqVideoCapture::~CpqVideoCapture()
{
  release();
}

bool
CpqVideoCapture::capture(int index)
{
  release();
  worker = CpqVideoCaptureWorker_private::getWorker(index);
  connectWorker();

  if (!worker->isOpened()) {
    release();
    return false;
  } else {
    emit captured();
    return true;
  }
}

bool
CpqVideoCapture::capture(QString file)
{

  release();
  worker = new CpqVideoCaptureWorker_private(file);
  connectWorker();

  if (!worker->isOpened()) {
    release();
    return false;
  } else {
    emit captured();
    return true;
  }
}

void
CpqVideoCapture::release()
{
  if (!(worker == nullptr)) {
    worker->clientRemove();
    worker = nullptr;
  }
  emit released();
}

bool
cpq::vis::CpqVideoCapture::checkFrameSender()
{
  return sender() == worker;
}

void
cpq::vis::CpqVideoCapture::connectWorker()
{
  connect(worker,
          &CpqVideoCaptureWorker_private::frameCaptured,
          this,
          &CpqVideoCapture::onFrameCaptured);

  connect(worker,
          &CpqVideoCaptureWorker_private::jpegCaptured,
          this,
          &CpqVideoCapture::onJpegCaptured);
}

void
CpqVideoCapture::onFrameCaptured(cpq::vis::CpqMat mat)
{
  if (checkFrameSender()) {
    emit frameCaptured(mat);
  }
}
void
CpqVideoCapture::onJpegCaptured(QByteArray jpeg)
{

  if (checkFrameSender()) {
    emit jpegCaptured(jpeg);
  }
}

#endif