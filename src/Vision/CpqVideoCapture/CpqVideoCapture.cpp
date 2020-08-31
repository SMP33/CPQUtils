#include "CpqVideoCapture.h"

using namespace cpq;
using namespace vis;

#ifndef NO_OPENCV

#include <opencv2/opencv.hpp>

#include "CpqVideoCaptureWorker_private.h"

#endif

#ifdef NO_OPENCV
CpqVideoCapture::CpqVideoCapture(QObject* parent)
  : QObject(parent)
{
  NO_CV_WARNING()
}

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
bool
CpqVideoCapture::capture(int index)
{
  worker = new CpqVideoCaptureWorker_private(index, nullptr);
  connect(worker,
          CpqVideoCaptureWorker_private::frameCaptured,
          this,
          CpqVideoCapture::frameCaptured);

  worker->start();
}

bool
CpqVideoCapture::capture(QString filename)
{}

void
CpqVideoCapture::release()
{}

#endif
