#ifndef CPQVIDEOCAPTUREWORKER_PRIVATE_H
#define CPQVIDEOCAPTUREWORKER_PRIVATE_H

#include <QMap>
#include <QMutex>
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
  explicit CpqVideoCaptureWorker_private(QString camera);
  bool isOpened() const;

  ~CpqVideoCaptureWorker_private();

public slots:
  void release();

signals:
  void frameCaptured(cpq::vis::CpqMat mat);
  void jpegCaptured(QByteArray jpeg);

protected:
  void run();

private:
  bool continueRun() const;
  bool m_continueRun = true;

  QMutex mutex;
  bool m_isOpened = false;
  cv::VideoCapture capture;
  QMap<QString, QSharedPointer<CpqVideoCaptureWorker_private>> cameras;
};
}
}
#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
