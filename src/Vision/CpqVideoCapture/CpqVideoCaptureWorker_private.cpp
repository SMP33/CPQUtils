#ifndef NO_OPENCV

#include "CpqVideoCaptureWorker_private.h"

using namespace cpq::vis;
using namespace cv;

QMutex* CpqVideoCaptureWorker_private::static_mutex = new QMutex();
QMap<int, CpqVideoCaptureWorker_private*>*
  CpqVideoCaptureWorker_private::static_cameras =
    new QMap<int, CpqVideoCaptureWorker_private*>;

bool
isNumber(QString str)
{
  bool isNum = false;
  str.toInt(&isNum);

  return isNum;
}

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(QString url)
  : QObject(nullptr)
  , m_url(url)
  , captureType(Type::URL)
{
  capture = VideoCapture(url.toStdString());

  m_isOpened = capture.isOpened();
  start();
  clientAdd();
}

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(int index)
  : QObject(nullptr)
  , m_index(index)
  , captureType(Type::INDEX)
{

  capture = VideoCapture(index);
  m_isOpened = capture.isOpened();

start();
}

void
cpq::vis::CpqVideoCaptureWorker_private::release()
{

  if (captureType == INDEX) {
    static_cameras->remove(m_index);
  } else {
  }

    deleteLater();
}

bool
cpq::vis::CpqVideoCaptureWorker_private::isOpened() const
{
  return m_isOpened;
}

void
cpq::vis::CpqVideoCaptureWorker_private::clientAdd()
{
  m_count++;
}

bool
cpq::vis::CpqVideoCaptureWorker_private::clientsCount() const
{
  return m_count;
}

void
cpq::vis::CpqVideoCaptureWorker_private::clientRemove()
{
  m_count--;
  bool ok = m_count;

  if (!ok) {
    release();
  }
}

CpqVideoCaptureWorker_private*
CpqVideoCaptureWorker_private::getWorker(int index)
{
  QMutexLocker lock_static(static_mutex);

  if (!static_cameras->contains(index)) {
    static_cameras->insert(index, new CpqVideoCaptureWorker_private(index));
  }

  static_cameras->operator[](index)->clientAdd();
  return static_cameras->operator[](index);
}

void
cpq::vis::CpqVideoCaptureWorker_private::start()
{
  if (m_isOpened) {
    //timer.setTimerType(Qt::TimerType::PreciseTimer);
    timer.start(30);
    timer.callOnTimeout(this, &CpqVideoCaptureWorker_private::onGrabbed);
  }
}

void
CpqVideoCaptureWorker_private::onGrabbed()
{
  Mat mat;
  Mat local_mat;
  if (capture.read(mat)) {

    mat.copyTo(local_mat);

    CpqMat m(local_mat);
    // this->usleep(1e3);

    emit frameCaptured(m);
    emit jpegCaptured(mat2Jpeg(m));
  }
}

#endif
