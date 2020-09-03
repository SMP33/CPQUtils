#ifndef NO_OPENCV

#include "CpqVideoCaptureWorker_private.h"

using namespace cpq::vis;
using namespace cv;

QMutex* CpqVideoCaptureWorker_private::static_mutex = new QMutex();
QMap<QString, CpqVideoCaptureWorker_private*>*
  CpqVideoCaptureWorker_private::static_cameras =
    new QMap<QString, CpqVideoCaptureWorker_private*>;

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(QString url)
  : QThread(nullptr)
  , m_url(url)
{
  bool isInt = false;
  url.toInt(&isInt);

  if (isInt) {
    capture = VideoCapture(url.toInt());
  } else {
    capture = VideoCapture(url.toStdString());
  }

  m_isOpened = capture.isOpened();

  if (m_isOpened) {
    start();
  }
}

void
cpq::vis::CpqVideoCaptureWorker_private::release()
{
  QMutexLocker lock(&mutex);
  QMutexLocker lock_static(static_mutex);

  static_cameras->remove(m_url);
  m_continueRun = false;

  qDebug() << "Release camera";
}

bool
cpq::vis::CpqVideoCaptureWorker_private::isOpened() const
{
  QMutexLocker lock(&mutex);
  return m_isOpened;
}

void
cpq::vis::CpqVideoCaptureWorker_private::clientAdd()
{
  QMutexLocker lock(&mutex);
  m_count++;
  qDebug() << "+";
}

void
cpq::vis::CpqVideoCaptureWorker_private::clientRemove()
{
  qDebug() << "-";
  mutex.lock();
  m_count--;
  bool ok = m_count;
  qDebug() << m_count;
  mutex.unlock();

  if (!ok) {
    release();
  }
}

CpqVideoCaptureWorker_private*
CpqVideoCaptureWorker_private::getWorker(QString url)
{
  QMutexLocker lock_static(static_mutex);

  if (!static_cameras->contains(url)) {
    static_cameras->insert(url, new CpqVideoCaptureWorker_private(url));
  }


  static_cameras->operator[](url)->clientAdd();
  return static_cameras->operator[](url);
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
  qDebug() << capture.isOpened();

  deleteLater();
}

bool
cpq::vis::CpqVideoCaptureWorker_private::continueRun() const
{
  return m_continueRun;
}

#endif
