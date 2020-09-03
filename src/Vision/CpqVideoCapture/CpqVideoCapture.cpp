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
  return capture(QString::number(index));
}

bool
CpqVideoCapture::capture(QString file)
{

  release();
  worker = CpqVideoCaptureWorker_private::getWorker(file);

  connect(worker,
          &CpqVideoCaptureWorker_private::frameCaptured,
          this,
          &CpqVideoCapture::frameCaptured);

  connect(worker,
          &CpqVideoCaptureWorker_private::jpegCaptured,
          this,
          &CpqVideoCapture::jpegCaptured);

  return worker->isOpened();
}

void
CpqVideoCapture::release()
{
  if (!(worker == nullptr)) {
    worker->clientRemove();
    worker = nullptr;
  }
}

#endif