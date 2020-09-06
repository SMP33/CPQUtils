#ifndef NO_OPENCV

#include "CpqVideoCaptureWorker_private.h"
#include "qcoreapplication.h"

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
  : QThread(new QThread)
  , m_url(url)
  , captureType(Type::URL)
{
  capture = VideoCapture(url.toStdString());

  m_isOpened = capture.isOpened();

  if (m_isOpened) {
    start();
  }
  clientAdd();
}

CpqVideoCaptureWorker_private::CpqVideoCaptureWorker_private(int index)
  : QThread(new QThread)
  , m_index(index)
  , captureType(Type::INDEX)
{

  capture = VideoCapture(index);
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

  if (captureType == INDEX) {
    static_cameras->remove(m_index);
  } else {
  }

  connect(this, &QObject::destroyed, [=]() {});

  if (!m_isOpened) {
    deleteLater();
  } else {
    m_continueRun = false;
    connect(this, &QThread::finished, this, &QObject::deleteLater);
  }
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
}

bool
cpq::vis::CpqVideoCaptureWorker_private::clientsCount() const
{
  QMutexLocker lock(&mutex);
  return m_count;
}

void
cpq::vis::CpqVideoCaptureWorker_private::clientRemove()
{
  mutex.lock();
  m_count--;
  bool ok = m_count;
  mutex.unlock();

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
CpqVideoCaptureWorker_private::run()
{
  Mat mat;
  QElapsedTimer timer;
  int fps = 0;
  timer.start();

  while (continueRun()) {
    if (capture.read(mat)) {

      CpqMat m(mat);
      //this->usleep(1e3);

      emit frameCaptured(m);
      emit jpegCaptured(mat2Jpeg(m));
    }
    fps++;
    if (timer.nsecsElapsed() > 1e9) {
      qDebug() << "fps:" << fps;
      fps = 0;
      timer.restart();
    }
  }
  // deleteLater();
}

bool
cpq::vis::CpqVideoCaptureWorker_private::continueRun() const
{
  QMutexLocker lock(&mutex);
  return m_continueRun;
}

#endif
