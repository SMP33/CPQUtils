#ifndef CPQVIDEOCAPTUREWORKER_PRIVATE_H
#define CPQVIDEOCAPTUREWORKER_PRIVATE_H

#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QSharedPointer>
#include <QThread>

#include <opencv2/opencv.hpp>

#include "../QCVTypes.h"

namespace cpq {
namespace vis {

class CpqVideoCaptureWorker_private : public QThread
{
  Q_OBJECT
public:
  bool isOpened() const;

  void clientAdd();
  void clientRemove();

  static CpqVideoCaptureWorker_private* getWorker(QString url);

public slots:
  void release();

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);

protected:
  void run();

private:
  explicit CpqVideoCaptureWorker_private(QString url);

  mutable QMutex mutex;

  bool continueRun() const;
  bool m_continueRun = true;
  bool m_isOpened = false;

  unsigned int m_count = 0;

  QString m_url;

  cv::VideoCapture capture;

  static QMutex* static_mutex;
  static QMap<QString, CpqVideoCaptureWorker_private*>* static_cameras;
};
}
}
#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
